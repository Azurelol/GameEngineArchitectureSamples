#pragma once

#include "ImGuiBinding.h"
#include "../Window/WindowSDL.h"

// Reference:
// https://github.com/ocornut/imgui/blob/master/examples/sdl_opengl_example/imgui_impl_sdl.cpp

namespace Systems {

  class ImGuiBindingSDL : public ImGuiBinding {

    static ImGuiBindingSDL* Instance;

  public:
    ImGuiBindingSDL();
    ~ImGuiBindingSDL();
    void PollEvents();
    void UpdateTimeStep();
    void UpdateInput();
    bool BindInput();
    void RenderDrawLists();
    static const char* GetClipboardText();
    static void SetClipboardText(const char* text);

  };

}
