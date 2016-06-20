#pragma once

#include <memory>
#include <vector>

namespace SPEngine {

  class System {
  public:
    using StrongPtr = std::unique_ptr<System>;
    using Container = std::vector<StrongPtr>;
    virtual void Update(float dt) = 0;
  };
  
  namespace Systems {

    enum class Enumerated {
      Physics,
      Graphics
    };

    class PhysicsSystem : public System {
    public:

      void Update(float dt) {
        Step(dt);
      }

      void Step(float dt);

      void Integrate();
      void BroadPhaseDetection();
      void NarrowPhaseDetection();
      void Resolve();
      void Publish();
    };

    class GraphicsSystem : public System {
    public:

      void Update(float dt) {
        RenderSprites();
        RenderShadows();
        RenderDebug();
      }

      void RenderSprites();
      void RenderDebug();
      void RenderShadows();

    };





  }
}