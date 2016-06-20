#pragma once

// STL
#include <memory>
// Settings
#include "WindowSettings.h"
// API
#include <SFML\Window.hpp>

  namespace Systems {

    class WindowSFML {

      sf::ContextSettings ContextSettings;
      std::unique_ptr<sf::Window> Context;
      sf::Event CurrentEvent;
      WindowSettings& Settings;

    public:
      WindowSFML(WindowSettings& settings) : Settings(settings) {}
      bool Initialize();
      void Terminate();
      void StartFrame();
      void EndFrame();
      void PollEvents();

      void PollInput();
      void PollKeyPressed();
      void PollMouseButtonPressed();
      void SetContextSettings();
    };

  }
