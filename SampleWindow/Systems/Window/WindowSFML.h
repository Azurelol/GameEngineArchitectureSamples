#pragma once

// Settings
#include "WindowInterface.h"
// API
#include <SFML\Window.hpp>

  namespace Systems {

    class WindowSFML : public WindowInterface {

      static WindowSFML* Instance;
      sf::ContextSettings ContextSettings;
      std::unique_ptr<sf::Window> Context;
      sf::Event CurrentEvent;

    public:
      //------------------------------------------------------------/
      WindowSFML(WindowSettings& settings);
      ~WindowSFML();
      bool Initialize();
      void Terminate();
      void StartFrame();
      void EndFrame();
      void PollEvents();
      //------------------------------------------------------------/
      void PollInput();
      void PollKeyPressed();
      void PollMouseButtonPressed();
      void SetContextSettings();
      //------------------------------------------------------------/
      static const sf::Event& getCurrentEvent() { return Instance->CurrentEvent; }
      static const sf::Window* getContext() { return Instance->Context.get(); }

    };

  }
