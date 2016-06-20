#pragma once
#include "../System.h"

// Since in this sample I will be writing the editor implementation code
// in the driver, we will go ahead and expose the API
#include "ImGuiBinding.h"

namespace Systems {

  class GUI : public System {

    std::unique_ptr<ImGuiBinding> Binding;

  public:
    GUI();
    void Initialize();
    void Update(float dt);
    void Terminate();
    void StartFrame();
    void EndFrame();
    bool IsCapturingMouse();
    bool IsCapturingKeyboard();

  };

}
