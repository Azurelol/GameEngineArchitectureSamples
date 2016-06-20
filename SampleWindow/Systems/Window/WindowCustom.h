#pragma once

// Settings
#include "WindowSettings.h"

  namespace Systems {

    class WindowCustom {

      WindowSettings& Settings;

    public:
      //------------------------------------------------------------/
      WindowCustom(WindowSettings& settings) : Settings(settings) {}
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
    };

  }
