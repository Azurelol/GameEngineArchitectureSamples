/*****************************************************************************/
/*!
\file   Component.cpp
\author Christian Sagel
\par    email: c.sagel\@digipen.edu
\date   4/17/2016
\brief  The base component class.
*/
/******************************************************************************/
#include "Component.h"

// To set references...
#include "..\Entity\EntitiesInclude.h"

namespace SPEngine {

  /**************************************************************************/
  /*!
  @brief Component constructor
  */
  /**************************************************************************/
  Component::Component(std::string name, Entity * owner) : Object(name), 
    OwnerRef(owner), SpaceRef(nullptr), GameSessionRef(nullptr)
  {
  }

  Component::Component() : Object("Component"),
    OwnerRef(nullptr), SpaceRef(nullptr), GameSessionRef(nullptr)
  {
  }

  Component::~Component()
  {
  }

  void Component::PostDefaultConstructor()
  {
    
  }

  /**************************************************************************/
  /*!
  @brief Configures the component, setting its references.
  */
  /**************************************************************************/
  void Component::Configure()
  {
    // GameObject
    if (auto gameObject = dynamic_cast<GameObject*>(OwnerRef)) {
      SpaceRef = gameObject->getSpace();
      GameSessionRef = gameObject->getGameSession();
    }
  }

  Entity * Component::Owner()
  {
    return OwnerRef;
  }

  Space * Component::getSpace() const
  {
    return const_cast<Space*>(SpaceRef);
  }

  GameSession * Component::getGameSession() const
  {
    return const_cast<GameSession*>(GameSessionRef);
  }
  
}