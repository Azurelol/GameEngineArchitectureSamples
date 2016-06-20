#include "WindowSDL.h"

// References
// http://www.aaroncox.net/tutorials/2dtutorials/sdlwindow.html
// http://lazyfoo.net/SDL_tutorials/lesson09/

  namespace Systems {

    WindowSDL* WindowSDL::Instance = nullptr;

    WindowSDL::WindowSDL(WindowSettings & settings) : WindowInterface(settings)
    {
      Instance = this;
    }

    WindowSDL::~WindowSDL()
    {
      Instance = nullptr;
      SDL_GL_DeleteContext(OpenGLContext);
      SDL_DestroyWindow(WindowContext);
    }

    bool WindowSDL::Initialize()
    {
      // Initializes the video component of SDL
      if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Error: %s\n", SDL_GetError());
        return false;
      }

      // Setup the window
      SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
      SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
      SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
      SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
      SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
      SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
      SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
      SDL_DisplayMode current;
      SDL_GetCurrentDisplayMode(0, &current);
      WindowContext = SDL_CreateWindow(Settings.Caption.c_str(), SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, Settings.ScreenWidth, Settings.ScreenHeight,
                                 SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

      OpenGLContext = SDL_GL_CreateContext(WindowContext);

      // Create the window
      //Context = SDL_CreateWindow(Settings.Caption.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
      //  Settings.ScreenWidth, Settings.ScreenHeight, SDL_WINDOW_SHOWN);

      if (!WindowContext)
        return false;

      return true;
    }

    void WindowSDL::Terminate()
    {      
      SDL_Quit();
    }

    void WindowSDL::StartFrame()
    {
    }

    void WindowSDL::EndFrame()
    {
      SDL_GL_SwapWindow(WindowContext);
    }

    void WindowSDL::PollEvents(const PollEventCallbackContainer& callbacks)
    {
      if (SDL_PollEvent(&CurrentEvent)) {
        if (CurrentEvent.type == SDL_QUIT) {
          Settings.OnClose();
        }

        PollInput();

        // Call every function that has subscribed to be notified when
        // this system is polling for events
        for (auto& callback : callbacks) {
          callback();
        }

      }
    }

    void WindowSDL::PollInput()
    {
      switch (CurrentEvent.type) {
      case SDL_KEYDOWN:
        PollKeyPressed();
        break;
      case SDL_MOUSEBUTTONDOWN:
        PollMouseButtonPressed();
        break;
      }
    }

    void WindowSDL::PollKeyPressed()
    {
      Keys key;

      switch (CurrentEvent.key.keysym.sym) {
      case SDLK_ESCAPE:
        key = Keys::Escape;
        std::cout << "'Escape' key pressed! \n";
        break;
      case SDLK_a:
        key = Keys::A;
        std::cout << "'A' key pressed! \n";
        break;
      }
    }

    void WindowSDL::PollMouseButtonPressed()
    {
      Buttons button;

      switch (CurrentEvent.button.button) {
      case SDL_BUTTON_LEFT:
        button = Buttons::Left;
        std::cout << "'Left' button pressed! \n";
        break;
      }
    }

  }


