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
#include "RigidBody.h"

// Need to know what an Entity is!
#include "../Objects/Entity/Entity.h"

namespace SZEngine {
  namespace Components {

    /**************************************************************************/
    /*!
    @brief Provides the definition of this class to Zilch.
    @note This can only go in the translational unit (.cpp)
    */
    /**************************************************************************/
    ZilchDefineType(RigidBody, "RigidBody", SZEngineCore, builder, type) {
      SZE_BINDING_SET_HANDLE_TYPE_POINTER;
      // Properties
      SZE_BINDING_DEFINE_PROPERTY(RigidBody, Velocity);
      SZE_BINDING_DEFINE_PROPERTY(RigidBody, Mass);
      SZE_BINDING_DEFINE_PROPERTY(RigidBody, RotationLocked);
    }

    RigidBody::RigidBody(Entity & owner) : Component("RigidBody", &owner), 
      Mass(1.0f), RotationLocked(true)
    {
    }

    void RigidBody::Initialize()
    {
    }

    void RigidBody::Terminate()
    {
    }


  }
}

