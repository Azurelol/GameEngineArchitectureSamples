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
    ZilchDefineType(Transform, "Transform", SZEngineCore, builder, type) {
      // Constructor / Destructor
      SZE_BINDING_COMPONENT_DEFINE_CONSTRUCTOR(Transform);
      SZE_BINDING_SET_HANDLE_TYPE_POINTER;
      // Properties
      SZE_BINDING_DEFINE_PROPERTY(Transform, Translation);
      SZE_BINDING_DEFINE_PROPERTY(Transform, Rotation);
      SZE_BINDING_DEFINE_PROPERTY(Transform, Scale);
    }

    Transform::Transform(Entity & owner) : Component("Transform", &owner)
    {
    }

    void Transform::Initialize()
    {
    }

    void Transform::Terminate()
    {
    }


  }
}

