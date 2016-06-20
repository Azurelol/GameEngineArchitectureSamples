#pragma once

// Settings
#include "WindowInterface.h"
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
      void PollEvents();
      //------------------------------------------------------------/
      void Subscribe(KeyDownCallback callback);
      void Subscribe(MouseDownCallback callback);
      void Subscribe(PollEventCallback callback);
      //------------------------------------------------------------/
      static void PollKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
      static void PollMouseButtonCallback(GLFWwindow* window, int button, int action, int mode);
      void PollKeyPressed(int keyPressed);
      void PollKeyReleased(int keyReleased);
      //------------------------------------------------------------/
      static GLFWwindow* getContext() { return Instance->Context; }

    };

  }
