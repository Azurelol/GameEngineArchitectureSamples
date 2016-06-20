#include "ZilchInterface.h"

namespace SZEngine {
  namespace Systems {

    /**************************************************************************/
    /*!
    @brief  Adds a Zilch script to the Zilch interface.
    @param  title The title of the script.
    @param  code Zilch code.
    @return The success of the operation.
    */
    /**************************************************************************/
    void ZilchInterface::AddScript(const std::string & title, const std::string & code)
    {
      // Look for duplicate
      for (auto& script : Scripts) {
        if (script.Name == title)
          return;
      }

      TraceFunction("Added '" + title + "'");

      // Create the struct
      ScriptInfo script(title, code);
      // Add it
      Scripts.push_back(script);
    }

    /**************************************************************************/
    /*!
    @brief  Adds a Zilch script to the Zilch interface.
    @param  fileName The name of the file containing the code.
    */
    /**************************************************************************/
    void ZilchInterface::AddScriptFromFile(const std::string & fileName)
    {
      // Look for duplicate
      for (auto& script : Scripts) {
        if (script.Name == fileName)
          return;
      }

      TraceFunction("Added '" + fileName + "'");

      // Open the file
      std::ifstream file(fileName);
      if (file) {
        // Read the string
        std::string code((std::istreambuf_iterator<char>(file)),
          (std::istreambuf_iterator<char>()));
        // Close the file
        file.close();
        // Create the struct
        ScriptInfo script(fileName, code);
        // Add it
        Scripts.push_back(script);
      }

    }


    /**************************************************************************/
    /*!
    @brief  Adds a Zilch script to a Zilch Project.
    @param  origin The display name of the code.
    @param  code The string containing the code.
    @return The success of the operation.
    */
    /**************************************************************************/
    bool ZilchInterface::LoadScriptFromString(Zilch::Project & project, const std::string & origin, const std::string & code)
    {
      TraceFunction("Loading '" + origin + "'");
      project.AddCodeFromString(code.c_str(), origin.c_str());
      return true;
    }


    /**************************************************************************/
    /*!
    @brief  Adds a Zilch script to a Zilch Project.
    @param  fileName The name of the file containing the code.
    @return The success of the operation.
    */
    /**************************************************************************/
    bool ZilchInterface::LoadScriptFromFile(Zilch::Project & project, const std::string & fileName)
    {
      TraceFunction("Loading '" + fileName + "'");
      bool success = project.AddCodeFromFile(fileName.c_str());
      ErrorIf(!success, std::string("AddCodeFromFile - Failed to add script:  '" + fileName + "'").c_str());
      return success;
    }

    //------------------------------------------------------------------------/
    // Callbacks
    //------------------------------------------------------------------------/
    /**************************************************************************/
    /*!
    @brief  Receives Zilch errors and redirects them to our logging system!
    @param  error A pointer to the error event.
    */
    /**************************************************************************/
    void FreeCustomErrorCallback(Zilch::ErrorEvent * error)
    {
      std::string errorMessage = error->GetFormattedMessage(Zilch::MessageFormat::Zilch).c_str();
      // Redirect to our tracing system
      TraceSimple(errorMessage);
    }

    /**************************************************************************/
    /*!
    @brief Receives Zilch parse events.
    @param event A pointer to the parse event.
    */
    /**************************************************************************/
    void FreeTypeParserCallback(Zilch::ParseEvent* event) {

    }


    /**************************************************************************/
    /*!
    @brief Receives Zilch pre-parse events.
    @param event A pointer to the parse event.
    */
    /**************************************************************************/
    void FreePreParserCallback(Zilch::ParseEvent* event) {

    }


    /**************************************************************************/
    /*!
    @brief Configures various callback functions on the specified project.
    @param project A reference to the project.
    */
    /**************************************************************************/
    void ZilchInterface::SetupProject(Zilch::Project & project)
    {
      Zilch::EventConnect(&project, Zilch::Events::CompilationError, FreeCustomErrorCallback);
      Zilch::EventConnect(&project, Zilch::Events::TypeParsed, FreeTypeParserCallback);
      Zilch::EventConnect(&project, Zilch::Events::PreParser, FreePreParserCallback);
    }

    /**************************************************************************/
    /*!
    @brief  Adds a Zilch library to the interface's dependencies module.
    @param  library A reference to the library to add.
    */
    /**************************************************************************/
    void ZilchInterface::AddLibrary(const Zilch::LibraryRef & library)
    {
      TraceFunction("Adding library");
      Dependencies.push_back(library);
    }



  }
}