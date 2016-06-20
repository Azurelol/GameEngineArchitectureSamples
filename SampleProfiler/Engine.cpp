#include "Engine.h"

namespace SPEngine {

  std::unique_ptr<Engine> SampleEngine = nullptr;

  void Engine::Initialize() {
    // Add the systems to the engine
    ActiveSystems.push_back(System::StrongPtr(new Systems::PhysicsSystem()));
    ActiveSystems.push_back(System::StrongPtr(new Systems::GraphicsSystem()));
  }

  void Engine::Terminate() {
  }

  void Engine::Update(float dt) {
    for (auto& system : ActiveSystems) {
      system->Update(dt);
    }
  }

}