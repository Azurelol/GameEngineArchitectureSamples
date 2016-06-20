#pragma once
#include "ComponentReference.h"

namespace SZEngine {
  namespace Components {

    class RigidBody : public Component {

      Vec3 Velocity;
      Real Mass;
      Boolean RotationLocked;

    public:
      ZilchDeclareDerivedType(RigidBody, Component);
      RigidBody(Entity & owner);
      void Initialize();
      void Terminate();
      // Properties
      SZE_DEFINE_PROPERTY(Vec3, Velocity);
      SZE_DEFINE_PROPERTY(Real, Mass);
      SZE_DEFINE_PROPERTY(Boolean, RotationLocked);


    };


  }
}