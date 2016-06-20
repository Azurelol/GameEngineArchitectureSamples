#pragma once

// These would be already included in a PCH!
#include <string>
#include <iostream> // For debugging!
#include "../../Objects/Types.h"

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
    bool FullScreen;
    std::string Caption;
    Vec2 Resolution;
    WindowSettings() : FullScreen(false), Resolution(Vec2(1024, 768)) {}
  };

}
