#include "Engine.h"

#include "..\Systems\SystemsInclude.h"
#include "..\Resources\ResourcesInclude.h"

namespace SPEngine {
  
  // Instance
  std::unique_ptr<Engine> SampleEngine;

  /**************************************************************************/
  /*!
  @brief Initializes the engine.
  @notes 1. Systems are added to a container in the engine.
        2. Creates the default local space, sets it as the active space.
        3. Specify which systems should be updated.
        4. All systems in the container are initialized.
  */
  /**************************************************************************/
  void Engine::Initialize() {
    SPTraceF;
    Active = true;

    //----------------------------------------------------------------------------/
    // Pretend that here you deserialized the system's settings from a file,
    // and they are now inside this object. You could have a struct of structs
    // to hold the settings of every major system, or just do it individually!
    //Systems::WindowSettings windowSettings;
    //windowSettings.Caption = "Sample Graphics - OpenGL"; 
    Systems.push_back(System::StrongPtr(new Systems::Window()));
    //----------------------------------------------------------------------------/
    for (auto& system : Systems)
      system->Initialize();
    //----------------------------------------------------------------------------/
    // Now we will create the default GameSession
    String projectName = "Sample Game";
    ActiveGameSession.reset(new GameSession(projectName));
    // Create a default space on it
    ActiveGameSession->DefaultSpace = ActiveGameSession->CreateNamedSpace("Sample Space");
    // Load a level on it
    Resources::Level::Ptr defaultLevel(new Resources::Level("Sample Level", "GameFolder\\NotReallyThere.Level"));
    ActiveGameSession->DefaultSpace->LoadLevel(defaultLevel);
  }

  /**************************************************************************/
  /*!
  @brief Updates the engine's systems.
  @param The time that elapsed during the last frame update.
  */
  /**************************************************************************/
  void Engine::Update(float dt) {
    getSystem<Systems::Window>()->StartFrame();

    for (auto& system : Systems)
      system->Update(dt);

    getSystem<Systems::Window>()->EndFrame();
  }

  /**************************************************************************/
  /*!
  @brief  Creates a timer and calls Update(dt) repeatedly.
  */
  /**************************************************************************/
  void Engine::Loop() {
    SPTraceF;
    while (Active) {
      Time::ScopeTimer frameTimer(&DeltaTime);
      Update(this->DeltaTime);
    }
  }

  /**************************************************************************/
  /*!
  @brief  Switches the engine off. On the next update when active has been
          recognized as false, it will start exit procedures then close.
  */
  /**************************************************************************/
  void Engine::Shutdown() {
    SPTraceF;
    Active = false;
  }

  /**************************************************************************/
  /*!
  @brief  Terminates all of the engine's systems.
  */
  /**************************************************************************/
  void Engine::Terminate() {
    SPTraceF;
    for (auto& system : Systems)
      system->Terminate();
  }
}