#pragma once

// Settings
#include "WindowInterface.h"
// API
#include <SDL\SDL.h>
// http://stackoverflow.com/questions/6847360/error-lnk2019-unresolved-external-symbol-main-referenced-in-function-tmainc
#undef main 
// Also make sure SDL2.dll is in the same directory as the the executable!

  namespace Systems {

    class WindowSDL : public WindowInterface {

      static WindowSDL* Instance;
      SDL_Window* WindowContext;
      SDL_GLContext OpenGLContext;
      SDL_Event CurrentEvent;

    public:
      //------------------------------------------------------------/
      WindowSDL(WindowSettings& settings);
      ~WindowSDL();
      bool Initialize();
      void Terminate();
      void StartFrame();
      void EndFrame();
      void PollEvents();
      //------------------------------------------------------------/
      void PollInput();
      void PollKeyPressed();
      void PollMouseButtonPressed();
      //------------------------------------------------------------/
      static const SDL_Event& getCurrentEvent() { return Instance->CurrentEvent; }
      static SDL_Window* getContext() { return Instance->WindowContext; }


    };

  }
