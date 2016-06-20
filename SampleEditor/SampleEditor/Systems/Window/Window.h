#pragma once
#include "..\System.h"

// Settings
#include "WindowSettings.h"
// Implementation
#include "WindowSFML.h"
#include "WindowSDL.h"
#include "WindowGLFW.h"

  namespace Systems {

    class Window : public System {

      // You should use a strong poitner instead (unique,shared)
      static Window* Instance;
      //----------------------------------------------------------------------------/
      WindowSettings Settings; // Can hold the settings in here or pass them by reference,
                               // having the engine itself "hold" them.
      std::unique_ptr<WindowInterface> Interface;
      //----------------------------------------------------------------------------/
      std::vector<WindowInterface::PollEventCallback> OnPollEventSubscribers;

    public:
      Window(WindowSettings settings);
      void Initialize();
      void Terminate();
      void StartFrame();
      void Update(float dt);
      void EndFrame();
            
      const WindowSettings& getSettings() { return Settings; }
      void Subscribe(WindowInterface::PollEventCallback callback);

      // Normally you wouldn't set the singleton instance this way... I am only
      // doing it this way since we don't have an engine class that owns this system 
      // at the moment.
      static void setInstance(Window* inst) { Instance = inst; }
      static Window* getInstance() { return Instance; }
      
      
    };

  }
