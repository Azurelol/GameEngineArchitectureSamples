/*****************************************************************************/
/*!
\file   Entity.cpp
\author Christian Sagel
\par    email: c.sagel\@digipen.edu
\date   4/17/2016
\brief  The base object composition class.
*/
/******************************************************************************/
#include "Entity.h"

// Serialization
#include "../../Systems/Scripting/ZilchInterface/ZilchInterface.h"

namespace SZEngine {

  /*!************************************************************************\
  @brief  Entity Definition
  \**************************************************************************/
  ZilchDefineType(Entity, "Entity", SZEngineCore, builder, type) {
    SZE_BINDING_SET_HANDLE_TYPE_POINTER;
    // Constructor
    ZilchBindConstructor(builder, type, Entity, "name", std::string);
    ZilchBindDestructor(builder, type, Entity);
    // Methods
    ZilchBindMethod(builder, type, &Entity::AddComponentByName, ZilchNoOverload, "AddComponentByName", "name, initialize");
    ZilchBindMethod(builder, type, &Entity::Destroy, ZilchNoOverload, "Destroy", ZilchNoNames);
  }

  /**************************************************************************/
  /*!
  @brief Entity constructor.
  @param name The name of the entity.
  */
  /**************************************************************************/
  Entity::Entity(std::string name) : Object(name)
  {
  }

  /**************************************************************************/
  /*!
  @brief  Entity destructor.
  */
  /**************************************************************************/
  Entity::~Entity()
  {
    // Zilch-made components
    for (auto& componentHandle : ActiveComponentsByHandle) {
      Component::Dereference(componentHandle)->Terminate();
      componentHandle.Delete();
    }
    ActiveComponentsByHandle.clear();
  }

  /**************************************************************************/
  /*!
  @brief  Adds the given component onto the Entity.
  @param  component A pointer to the component.
  @return A pointer to the component.
  @note   This is just a quick way to just quickly insert a component
          on the Entity rather than having it done internally. So only
          do it this way for debugging! Use a component factory behind the
          scenes instead!
  */
  /**************************************************************************/
  Component::Ptr Entity::AddComponent(Component::Ptr component)
  {
    ActiveComponents.push_back(Component::StrongPtr(component));
    return component;
  }

  Component::Ptr Entity::AddComponent(Zilch::Handle componentHandle)
  {
    ActiveComponentsByHandle.push_back(componentHandle);
    return Component::Dereference(componentHandle);
  }

  /**************************************************************************/
  /*!
  @brief  Adds a component onto the entity by name.
  @param  name The name of the component.
  @bool   Whether to initialize the component.
  @return A pointer to the component.
  */
  /**************************************************************************/
  ComponentPtr Entity::AddComponentByName(const std::string & name, bool initialize)
  {
    return ComponentPtr();
  }

  /**************************************************************************/
  /*!
  @brief  Returns a container of pointers to the components this entity owns.
  @return A container of component pointers.
  */
  /**************************************************************************/
  ComponentContainer Entity::AllComponents()
  {
    // Fill the container of pointers to the components that this entity owns
    Component::Container components;
    for (auto& component : ActiveComponents) {
      components.push_back(component.get());
    }
    for (auto componentHandle : ActiveComponentsByHandle) {
      components.push_back(reinterpret_cast<Component*>(componentHandle.Dereference()));
    }
    return components;
  }

  /**************************************************************************/
  /*!
  @brief  Removes all components from the entity.
  */
  /**************************************************************************/
  void Entity::RemoveAllComponents()
  {
    // C++- Factory-made components
    for (auto& component : ActiveComponents) {
      component->Terminate();
    }
    ActiveComponents.clear();

    // Zilch-made components
    for (auto& componentHandle : ActiveComponentsByHandle) {
      Component::Dereference(componentHandle)->Terminate();
      componentHandle.Delete();
    }
    ActiveComponentsByHandle.clear();
  }

  /**************************************************************************/
  /*!
  @brief Serializes an entity. This will serialize all its underlying properties
         before serializing all its components.
  @param builder A reference to the JSON builder.
  @note  This will serialize the entity's properties, then its components.
  */
  /**************************************************************************/
  void Entity::Serialize(Zilch::JsonBuilder & builder)
  {
    // Grab a reference to the state
    auto state = Systems::ZilchInterface::getState();
    // Serialize Object-specific properties
    Object::Serialize(builder);
    // Serialize Entity-specific properties
    SerializeByType(builder, state, ZilchTypeId(Entity), this);
    //---------------------------------------------------------/
    // Now we serialize all its components
    builder.Key("Components");
    builder.Begin(Zilch::JsonType::Object);
    {
      // C++-managed components
      for (auto& component : ActiveComponents) {
        component->Serialize(builder);
      }
      // Zilch-managed components
      for (auto& componentHandle : ActiveComponentsByHandle) {
        Component::Dereference(componentHandle)->Serialize(builder);
      }

    }
    builder.End();
    //---------------------------------------------------------/
  }

  /**************************************************************************/
  /*!
  @brief Deserializes an entity
  @param properties A pointer to the object containing the properties.
  @note  This will deserialize the entity's properties, then its components.
  */
  /**************************************************************************/
  void Entity::Deserialize(Zilch::JsonValue * properties)
  {
    // Grab a reference to the state
    auto state = Systems::ZilchInterface::getState();
    // Deserialize it
    DeserializeByType(properties, state, ZilchTypeId(Entity), this);
    // Deserialize the object properties as well
    Object::Deserialize(properties);

  }

}