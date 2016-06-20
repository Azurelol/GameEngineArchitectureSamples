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
// Serialization
#include "../../Systems/Scripting/ZilchInterface/ZilchInterface.h"

namespace SZEngine {

  /*!************************************************************************\
  @brief  Component Definition
  \**************************************************************************/
  ZilchDefineType(Component, "Component", SZEngineCore, builder, type) {
    // This sets Zilch's Handle manager setting. Alternatively, use the macro!
    //type->HandleManager = ZilchManagerId(Zilch::PointerManager);
    SZE_BINDING_SET_HANDLE_TYPE_POINTER;     
    // Constructor / Destructor
    ZilchBindDestructor(builder, type, Component);
    // Methods
    ZilchBindMethod(builder, type, &Component::getSpace, ZilchNoOverload, "Space", ZilchNoNames);
    ZilchBindMethod(builder, type, &Component::getGameSession, ZilchNoOverload, "GameSession", ZilchNoNames);
    ZilchBindMethod(builder, type, &Component::Owner, ZilchNoOverload, "Owner", ZilchNoNames);
    ZilchBindMethod(builder, type, &Component::Initialize, ZilchNoOverload, "Initialize", ZilchNoNames);
  }

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

  void Component::PostDefaultConstructor(const std::string & name, Entity * owner)
  {
    setName(name);
    OwnerRef = owner;
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

  ComponentPtr Component::Dereference(const ComponentHandle & handle)
  {
    return reinterpret_cast<ComponentPtr>(handle.Dereference());
  }

  std::vector<Zilch::BoundType*> Component::All()
  {
    std::vector<Zilch::BoundType*> componentTypes;
    for (auto library : Systems::ZilchInterface::getLibraries().all()) {
      // Grab a container of all the bound types in the library
      auto types = library->BoundTypes.all();
      // For every type in the library
      ZilchForEach(auto type, types) {

        if (type.second->Name == "Component" || type.second->Name == "ZilchComponent")
          continue;

        if (Zilch::TypeBinding::IsA(type.second, ZilchTypeId(Component)))
          componentTypes.push_back(type.second);
      }
    }
    return componentTypes;
  }


  /**************************************************************************/
  /*!
  @brief Serializes a Component.
  @param builder A reference to the JSON builder.
  @note  This will serialize the component and all its properties.
  */
  /**************************************************************************/
  void Component::Serialize(Zilch::JsonBuilder & builder)
  {
    // Grab a reference to the state
    auto state = Systems::ZilchInterface::getState();

    // For components we use their name as the Key. We will use it
    // to look up for a match among known BoundTypes in order to construct it
    // later when deserializing!
    builder.Key(this->getName().c_str());
    builder.Begin(Zilch::JsonType::Object);
    {
      // For components we want to serialize the derived type, not the base
      // component class!
      SerializeByType(builder, state, this->ZilchGetDerivedType(), this);
    }
    builder.End();
  }

  /**************************************************************************/
  /*!
  @brief Deserializes a Component.
  @param builder A pointer to the object containing the properties.
  @note  This will deserialize the Component's properties.
  */
  /**************************************************************************/
  void Component::Deserialize(Zilch::JsonValue * properties)
  {
    // Grab a reference to the state
    auto state = Systems::ZilchInterface::getState();
    DeserializeByType(properties, state, this->ZilchGetDerivedType(), this);
  }

}