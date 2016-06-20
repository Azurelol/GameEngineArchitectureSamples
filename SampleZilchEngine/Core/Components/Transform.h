/******************************************************************************/
/*!
@file   Transform.h
@author Christian Sagel
@par    email: c.sagel\@digipen.edu
@date   4/25/2016
@brief  The transform component allows the representation of this object in
        world space, allowing it to be drawn, take part in collisions and
        force-based movement through the addition of other components.
*/
/******************************************************************************/
#pragma once
#include "ComponentReference.h"

namespace SZEngine {
  namespace Components {

    class Transform : public Component {
      Vec3 Translation;
      Vec3 Rotation;
      Vec3 Scale;

    public:
      ZilchDeclareDerivedType(Transform, Component);
      Transform(Entity & owner);
      void Initialize();
      void Terminate();
      // Properties
      SZE_DEFINE_PROPERTY(Vec3, Translation);
      SZE_DEFINE_PROPERTY(Vec3, Rotation);
      SZE_DEFINE_PROPERTY(Vec3, Scale);


    };


  }
}