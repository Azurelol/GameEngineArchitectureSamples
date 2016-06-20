#pragma once

#include "Systems.h"
#include "Profiler.h"

namespace SPEngine {
  
  class Engine;
  extern std::unique_ptr<Engine> SampleEngine;

  class Engine {

    Profiler ProfilerObj;
    float FrameRate;
    float DeltaTime;
    System::Container ActiveSystems;

  public:

    Engine() : FrameRate(60.0f), DeltaTime(1.0f / FrameRate) {}
    ~Engine() {}

    void Initialize();
    void Terminate();
    void Update(float dt);

    static float Dt() { return SampleEngine->DeltaTime; }    
    static Profiler& Profiler() { return SampleEngine->ProfilerObj; }


  };


}

