/******************************************************************************/
/*!
@file   CoreBinding.cpp
@author Christian Sagel
@par    email: c.sagel\@digipen.edu
@date   4/23/2016
@brief  This file includes the definition of the static library for all the
        Core engine classes (Object, Entities, Components).
*/
/******************************************************************************/
#include "CoreBinding.h"

// Bound Types
#include "..\Objects\ObjectsInclude.h"
#include "..\Objects\Entity\EntitiesInclude.h"
#include "..\Components\ComponentsInclude.h"
#include "..\Resources\ResourcesInclude.h"

namespace SZEngine {

  ZilchDefineStaticLibrary(SZEngineCore) {
        
     // We have to initialize all the types that we have bound to our library inside this scope.
     // Ideally we could use pre-main or automatic registration, but there's a major issues where
     // compilers automatically remove "unreferenced" classes, even if they are referenced
     // by globals/pre-main initializations. This method ensures that all classes will be properly bound.
    
        
    // Objects
    ZilchInitializeType(Object);
    ZilchInitializeType(Entity);
    ZilchInitializeType(Component);
    ZilchInitializeType(ZilchComponent);
    ZilchInitializeType(GameObject);
    ZilchInitializeType(Space);
    ZilchInitializeType(GameSession);
    ZilchInitializeType(Resource);

    // Components
    ZilchInitializeType(Components::Transform);
    ZilchInitializeType(Components::RigidBody);
    // A version of the the Transform component that is
    // constructed through Zilch's memory manager
    ZilchInitializeType(Components::TransformZilch);

  }

}
