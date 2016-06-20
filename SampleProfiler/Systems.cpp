#include "Systems.h"

#include "Profiler.h"

namespace SPEngine {
  namespace Systems {

    void PhysicsSystem::Step(float dt) {
      SystemMethodTimer(__FUNCTION__, Enumerated::Physics);
      Integrate();
      BroadPhaseDetection();
      NarrowPhaseDetection();
      Resolve();
      Publish();
    }
    void PhysicsSystem::Integrate() { SystemMethodTimer(__FUNCTION__, Enumerated::Physics); }
    void PhysicsSystem::BroadPhaseDetection() { SystemMethodTimer(__FUNCTION__, Enumerated::Physics); }
    void PhysicsSystem::NarrowPhaseDetection() { SystemMethodTimer(__FUNCTION__, Enumerated::Physics); }
    void PhysicsSystem::Resolve() { SystemMethodTimer(__FUNCTION__, Enumerated::Physics); }
    void PhysicsSystem::Publish() {
      SystemMethodTimer(__FUNCTION__, Enumerated::Physics);

    }

    void GraphicsSystem::RenderSprites() { SystemMethodTimer(__FUNCTION__, Enumerated::Graphics); }
    void GraphicsSystem::RenderDebug() { SystemMethodTimer(__FUNCTION__, Enumerated::Graphics); }
    void GraphicsSystem::RenderShadows() { SystemMethodTimer(__FUNCTION__, Enumerated::Graphics); }
  }
}