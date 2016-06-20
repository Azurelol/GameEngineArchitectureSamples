#pragma once

#include <string>
#include <memory>
#include <iostream> // For debugging!
#include <vector>
#include <functional> // std::function

  enum class Buttons {
    Left,
    Middle,
    Right
  };

  enum class Keys {
    Null,
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
      using CloseCallback = std::function<void(void)>;
      //----------------------------------------------------------------------/
      API Interface;
      bool FullScreen;
      std::string Caption;
      int ScreenWidth;
      int ScreenHeight;
      CloseCallback OnClose;
      WindowSettings() : Interface(API::SFML), FullScreen(false), ScreenWidth(1024), ScreenHeight(768) {}      
    };



  }

