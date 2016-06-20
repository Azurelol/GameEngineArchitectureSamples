/******************************************************************************/
/*!
@file   ZilchInterface.cpp
@author Christian Sagel
@par    email: c.sagel\@digipen.edu
@date   4/20/2016
@brief  A class providing an interface to the Zilch state among other things.
*/
/******************************************************************************/
#include "ZilchInterface.h"

#include "../../../Binding/CoreBinding.h"

namespace SZEngine {
  namespace Systems {

    // Initialize the static global pointer
    ZilchInterface* ZilchInterface::Instance = nullptr;

    /**************************************************************************/
    /*!
    @brief  ZilchInterface Constructor.
    */
    /**************************************************************************/
    ZilchInterface::ZilchInterface() : Setup(Zilch::StartupFlags::None)
    {
      Instance = this;
    }

    /**************************************************************************/
    /*!
    @brief  ZilchInterface Destructor.
    */
    /**************************************************************************/
    ZilchInterface::~ZilchInterface()
    {
      Instance = nullptr;
    }

    /**************************************************************************/
    /*!
    @brief  Initializes the Zilch interface system. Any one time startup and
    static initialization Zilch needs to do
    This also registers a custom assertion handler (Zilch code has many
    user friendly asserts!)
    */
    /**************************************************************************/
    void ZilchInterface::Initialize()
    {
      TraceFunction("Setting up console, adding all libraries, linking state...");
      // Setup the console so that when we call 'Console.WriteLine' it outputs to stdio
      Zilch::EventConnect(&Zilch::Console::Events, Zilch::Events::ConsoleWrite, Zilch::DefaultWriteText);
      // We can also setup the console so that any 'Read' functions will attempt to read from stdin
      Zilch::EventConnect(&Zilch::Console::Events, Zilch::Events::ConsoleRead, Zilch::DefaultReadText);
      // Add all static libraries.
      AddLibrary(SZEngineCore::GetInstance().GetLibrary());
      // If patching, add a (for now empty) script library
      if (Patching) {
        Zilch::Project scriptProject;
        ScriptsLibrary = scriptProject.Compile("ZilchScripts", Dependencies, Zilch::EvaluationMode::Project);
        AddLibrary(ScriptsLibrary);
      }

      // Link the executable state
      Build();
    }

    /**************************************************************************/
    /*!
    @brief  Clears the interface's executable state as well as the dependencies
            module.
    */
    /**************************************************************************/
    void ZilchInterface::Terminate()
    {
      TraceFunction("");
      // Free the State's dynamically allocated memory
      if (State) {
        delete State; State = nullptr;
      }

      Report.Clear();
      Dependencies.clear();
    }

    /**************************************************************************/
    /*!
    @brief  Compiles and links all the libraries into one executable state.
    @return True if the state was linked successfully, false otherwise.
    */
    /**************************************************************************/
    bool ZilchInterface::Build()
    {
      TraceFunction("Compiling all libraries into executable state");
      State = Dependencies.Link();
      // If the linking failed...
      if (!State)
        return false;

      return true;
    }


    /**************************************************************************/
    /*!
    @brief  Compiles all our scripts into a single Zilch library.
    */
    /**************************************************************************/
    bool ZilchInterface::Compile()
    {
      // A project contains all of the code we combine together to make a single
      // Zilch library. The project also sends events for compilation errors that occur
      Zilch::Project scriptProject;
      // Here, we can register our own callback for when compilation errors occur
      // The default callback prints the file, line/character number, and message to stderr
      SetupProject(scriptProject);
      // Add code from the scripts stored so far
      for (auto& script : Scripts) {
        LoadScriptFromString(scriptProject, script.Name, script.Code);
      }

      // If not patching, clear dependencies and re-add the core libraries
      if (!Patching) {
        // HINT: This should be a function, instead!!
        Dependencies.clear();
        AddLibrary(Zilch::Core::GetInstance().GetLibrary());
        AddLibrary(SZEngineCore::GetInstance().GetLibrary());
      }

      // Compile all the code we have added together into a single library for our scripts
      auto lib = scriptProject.Compile("ZilchComponents", Dependencies, Zilch::EvaluationMode::Project);

      // If the script library compiled succesfully
      if (lib) {
        
        // Update the existing library
        ScriptsLibrary = lib;

        if (Patching) {
          State->PatchLibrary(ScriptsLibrary);
          TraceFunction("Successfully patched the script library!");
        }
        else {
          AddLibrary(ScriptsLibrary);
          Build();
          TraceFunction("Successfully rebuilt the executable state with the new script library!");
        }

        return true;
      }

      return false;
    }
  }
}