#include "Window.h"

namespace Systems {

  Window* Window::Instance = nullptr;

  Window::Window(WindowSettings settings) : System("Window"),
    Settings(settings), Implementation(Settings)
  {

  }
  void Window::Initialize()
  {
    TraceObject("");
    // If the window system failed to initialize, probably abort?
    if (!Implementation.Initialize()) {
      std::cout << __FUNCTION__ << ": Failed to initialize! \n";
    }
  }

  void Window::Terminate()
  {
    Implementation.Terminate();
  }

  void Window::StartFrame()
  {
    Implementation.StartFrame();
  }

  void Window::Update(float dt)
  {
    Implementation.PollEvents();
  }
  void Window::EndFrame()
  {
    Implementation.EndFrame();
  }
  const Vec2 & Window::Resolution()
  {
    return getInstance()->Settings.Resolution;
  }
}
