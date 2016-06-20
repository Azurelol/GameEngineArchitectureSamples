/******************************************************************************/
/*!
@file   ZilchInterface.h
@author Christian Sagel
@par    email: c.sagel\@digipen.edu
@date   4/20/2016
@brief  A class providing an interface to the Zilch state among other things.
*/
/******************************************************************************/
#pragma once

namespace SZEngine {
  namespace Systems {
    class ZilchInterface {
      
      //----------------------------------------------------------------------/
      struct ScriptInfo {
        std::string Name;
        std::string Code;
        ScriptInfo(const std::string& name, const std::string& code)
                   : Name(name), Code(code) {}
      };
      //----------------------------------------------------------------------/
      bool Patching;
      std::vector<ScriptInfo> Scripts;
      Zilch::LibraryRef ScriptsLibrary;
      bool LoadScriptFromString(Zilch::Project& project, const std::string& origin, const std::string& code);
      bool LoadScriptFromFile(Zilch::Project& project, const std::string& fileName);
      //----------------------------------------------------------------------/
      static ZilchInterface* Instance;
      Zilch::ZilchSetup Setup;
      Zilch::ExecutableState* State;
      Zilch::ExceptionReport Report;
      Zilch::Module Dependencies;
      //----------------------------------------------------------------------/
      void SetupProject(Zilch::Project& project);
      void AddLibrary(const Zilch::LibraryRef & library);
      bool Build();

    public:
      ZilchInterface();
      ~ZilchInterface();
      void Initialize();
      void Terminate();
      static Zilch::ExecutableState*& getState() { return Instance->State; }
      static Zilch::Module& getLibraries() { return Instance->Dependencies; }
      //static Zilch::LibraryRef& getScripts() { return }
      void AddScript(const std::string& title, const std::string& code);
      void AddScriptFromFile(const std::string& fileName);
      bool Compile();

    };

  }
}