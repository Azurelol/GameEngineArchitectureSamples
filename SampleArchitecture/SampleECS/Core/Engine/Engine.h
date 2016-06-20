#pragma once

#include "..\Systems\SystemReference.h"
#include "..\Libraries\Time\Timer.h"
#include "..\Objects\Entity\GameSession\GameSession.h"

namespace SPEngine {
  
  //------------------------------------------------/
  // Point of access for the engine as a singleton.
  // Anyone that includes this header will be able to access the singular
  // instance of the engine.
  //-----------------------------------------/
  class Engine;
  extern std::unique_ptr<Engine> SampleEngine;
  //-----------------------------------------/

  class Engine {
    float DeltaTime;
    bool Active;
    GameSession::StrongPtr ActiveGameSession;
    std::vector<System::StrongPtr> Systems;

  public:
    Engine() : DeltaTime(60.0f), Active(false) {}
    template<typename SystemClass> SystemClass* getSystem();

    void Initialize();
    void Update(float dt);
    void Loop();
    void Shutdown();
    void Terminate();

  };    

}

// Template definitions are best included in another file. For example:
#include "Engine.hpp"