#pragma once
#include "ComponentReference.h"

namespace Components {

  class Transform : public Component {
    float Position;
  public:
    Transform(Entity& owner) : Component("Transform", owner) {}
    void Initialize() {}
    void Terminate() {}
  };

}