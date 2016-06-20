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
#include "Transform.h"


  namespace Components {

    Transform::Transform(Entity & owner) : Component("Transform", &owner),
      Scale(1.0f, 1.0f, 1.0f)
    {
    }

    void Transform::Initialize()
    {
    }

    void Transform::Terminate()
    {
    }


  }


