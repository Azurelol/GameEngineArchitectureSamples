#pragma once
#include "..\SystemReference.h"

namespace SPEngine {
  namespace Systems {

    class Window : public System {

    public:

      Window();
      void Initialize();
      void Terminate();
      void StartFrame();
      void Update(float dt);
      void EndFrame();
      
    };

  }
}