/*****************************************************************************/
/*!
\file   Entity.h
\author Christian Sagel
\par    email: c.sagel\@digipen.edu
\date   4/17/2016
\brief  The base object composition class.
*/
/******************************************************************************/
#pragma once
#include "..\Object.h"

// Components
#include "..\Component\Component.h"

namespace SZEngine {

  class Entity : public Object {

    // Members
    std::string Archetype;
    ComponentStrongContainer ActiveComponents;
    ComponentHandleVec ActiveComponentsByHandle;

  public:
    
    ZilchDeclareDerivedType(Entity, Object);
    Entity(std::string name);
    ~Entity();
    // Properties
    SZE_DEFINE_PROPERTY(std::string, Archetype);
    // Interface
    virtual void Destroy() {}
    // Components
    Component::Ptr AddComponent(Component::Ptr component);
    Component::Ptr AddComponent(Zilch::Handle componentHandle);
    ComponentPtr AddComponentByName(const std::string& name, bool initialize);
    ComponentContainer AllComponents();
    void RemoveAllComponents();
    // Serialization
    void Serialize(Zilch::JsonBuilder& builder);
    void Deserialize(Zilch::JsonValue* properties);

  };






}