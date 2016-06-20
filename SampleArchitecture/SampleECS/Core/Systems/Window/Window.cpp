#include "Window.h"

namespace SPEngine {
  namespace Systems {

    Window::Window() : System("Window")
    {
    }
    void Window::Initialize()
    {
      SPTraceF;     
    }

    void Window::Terminate()
    {
      SPTraceF;
    }

    void Window::StartFrame()
    {
    }

    void Window::Update(float dt)
    {
    }

    void Window::EndFrame()
    {
    }
  }
}