#pragma once

#include <string>
#include <iostream> // For debugging!
#include <vector>
#include <functional> // std::function

  enum class Buttons {
    Left,
    Middle,
    Right
  };

  enum class Keys {
    Escape,
    A
  };

  namespace Systems {

    struct WindowSettings {
      //----------------------------------------------------------------------/
      enum class API {
        SFML,
        GLFW,
        SDL
      };
      // A function called when the window is closing
      using CloseCalback = std::function<void(void)>;
      //----------------------------------------------------------------------/
      API Interface;
      bool FullScreen;
      std::string Caption;
      int ScreenWidth;
      int ScreenHeight;
      CloseCalback OnClose;
      WindowSettings() : Interface(API::SFML), FullScreen(false), ScreenWidth(1024), ScreenHeight(768) {}      
    };

    class WindowInterface {
    protected:
      WindowSettings& Settings;
    public:
      // A function called when the window is polling for OS-specific window events
      using PollEventCallback = std::function<void(void)>;
      using PollEventCallbackContainer = std::vector<PollEventCallback>;

      WindowInterface(WindowSettings& settings) : Settings(settings) {}
      virtual bool Initialize() = 0;      
      virtual void Terminate()  = 0;
      virtual void StartFrame() = 0;
      virtual void EndFrame()   = 0;
      virtual void PollEvents(const PollEventCallbackContainer& callback) = 0;
    };

  }

