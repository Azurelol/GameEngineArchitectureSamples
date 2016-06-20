#include "GUI.h"

// Provided bindings (This has to go first or...)
#include "ImGuiBindingSFML.h"
#include "ImGuiBindingGLFW.h"
#include "ImGuiBindingSDL.h"

// What API will be used
#include "../Window/Window.h"

namespace Systems
{
  GUI::GUI()
  {    
    // Depending on what API the Window system is using we will be using different bindings
    switch (Window::getInstance()->getSettings().Interface) {
    case WindowSettings::API::SFML:
      Binding.reset(new ImGuiBindingSFML());
      break;
    case WindowSettings::API::SDL:
      Binding.reset(new ImGuiBindingSDL());
      break;
    case WindowSettings::API::GLFW:
      Binding.reset(new ImGuiBindingGLFW());
      break;
    }   
    
  }

  void GUI::Initialize()
  {
    Binding->Initialize();
  }

  void GUI::Update(float dt)
  {
    // Do stuff unrelated to the binding
  }

  void GUI::Terminate()
  {
    Binding->Terminate();
  }

  void GUI::StartFrame()
  {
    Binding->StartFrame();
  }

  void GUI::EndFrame()
  {
    Binding->EndFrame();
  }

  bool GUI::IsCapturingMouse()
  {
    return false;
  }

  bool GUI::IsCapturingKeyboard()
  {
    return false;
  }

}