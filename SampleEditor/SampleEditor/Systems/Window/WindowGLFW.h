#pragma once

// Settings
#include "WindowSettings.h"
// API
#include <GLFW\glfw3.h>

  namespace Systems {
    
    class WindowGLFW : public WindowInterface{

      static WindowGLFW* Instance;
      GLFWwindow* Context;

    public:
      //------------------------------------------------------------/
      WindowGLFW(WindowSettings& settings) : WindowInterface(settings) {}
      bool Initialize();
      void Terminate();
      void StartFrame();
      void EndFrame();
      void PollEvents(const PollEventCallbackContainer& callback);
      //------------------------------------------------------------/
      static void PollKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
      static void PollMouseButtonCallback(GLFWwindow* window, int button, int action, int mode);
      void PollKeyPressed(int keyPressed);
      void PollKeyReleased(int keyReleased);
      //------------------------------------------------------------/
      static GLFWwindow* getContext() { return Instance->Context; }

    };

  }
