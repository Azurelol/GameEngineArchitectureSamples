#pragma once
#include "ImGuiBinding.h"
#include "../Window/WindowGLFW.h"

namespace Systems {

  class ImGuiBindingGLFW : public ImGuiBinding {

    static ImGuiBindingGLFW* Instance;

  public:
    ImGuiBindingGLFW();
    ~ImGuiBindingGLFW();
    void PollEvents();
    void UpdateTimeStep();
    void UpdateInput();
    bool BindInput();
    void RenderDrawLists();
    // Callbacks
    static void OnMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void OnMouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
    static void OnKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void OnCharCallback(GLFWwindow* window, unsigned int c);
    static const char* GetClipboardText();
    static void SetClipboardText(const char* text);

  };

}
