#pragma once
#include "ComponentReference.h"

namespace Components {

  class Sprite : public Component {
  public:
    Sprite(Entity& owner) : Component("Sprite", owner) {}
    void Initialize() { TraceObject(""); }
    void Terminate() {}
  };

}