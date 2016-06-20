#include "Window.h"

namespace Systems {

  // Static members always need to be initialized in a .cpp
  Window* Window::Instance = nullptr;

  Window::Window(WindowSettings settings) : Settings(settings) {

    // Instantiates a different API interface object depending
    // on which API was chosen.
    switch (settings.Interface) {
    case WindowSettings::API::SFML:
      Settings.Caption = "Sample Editor using SFML!";
      Interface.reset(new Systems::WindowSFML(Settings));
      break;
    case WindowSettings::API::SDL:
      Settings.Caption = "Sample Editor using SDL!";
      Interface.reset(new Systems::WindowSDL(Settings));
      break;
    case WindowSettings::API::GLFW:
      Settings.Caption = "Sample Editor using GLFW!";
      Interface.reset(new Systems::WindowGLFW(Settings));
      break;

    }
  }
  void Window::Initialize()
  {
    // If the window system failed to initialize, probably abort?
    if (!Interface->Initialize()) {
      std::cout << __FUNCTION__ << ": Failed to initialize! \n";
    }
  }

  void Window::Terminate()
  {
    Interface->Terminate();
  }

  void Window::StartFrame()
  {
    Interface->StartFrame();
  }

  void Window::Update(float dt)
  {
    Interface->PollEvents(OnPollEventSubscribers);
  }

  void Window::EndFrame()
  {
    Interface->EndFrame();
  }

  void Window::Subscribe(WindowInterface::PollEventCallback callback)
  {
    OnPollEventSubscribers.push_back(callback);
  }
}
