/*****************************************************************************/
/*!
\file   Component.h
\author Christian Sagel
\par    email: c.sagel\@digipen.edu
\date   4/17/2016
\brief  The base component class.
*/
/******************************************************************************/
#pragma once
#include "..\Object.h"

namespace SZEngine {

  //---------------------------------------------------------------------------/
  // Forward declarations
  class Entity;
  class Space;
  class GameSession;
  //---------------------------------------------------------------------------/
  // Aliases (We use a forward declaration here in order to have the aliases available in the class itself)
  class Component;
  // Weak: To be shared and freely passed around.
  using ComponentPtr = Component*;
  using ComponentContainer = std::vector<ComponentPtr>;
  // Strong: To be used when allocating components yourself, for example with through a component factory
  using ComponentStrongPtr = std::unique_ptr<Component>;
  using ComponentStrongContainer = std::vector<ComponentStrongPtr>;
  // Handles: to be used when allocating components through Zilch's memory manager
  using ComponentHandle = Zilch::Handle;
  using ComponentHandleVec = std::vector<Zilch::Handle>;
  //---------------------------------------------------------------------------/

  class Component : public Object {
    Zilch::Handle Handle;
    Entity* OwnerRef;
    const Space* SpaceRef;
    const GameSession* GameSessionRef;

    void Configure();

  public:
    ZilchDeclareDerivedType(Component, Object);
    Component(std::string name, Entity* owner);
    Component();
    ~Component();
    void PostDefaultConstructor(const std::string& name, Entity* owner);
    // Aliases
    using Ptr = Component*;
    using StrongPtr = std::unique_ptr<Component>;
    using Container = std::vector<Ptr>;
    // Interface
    Entity* Owner();
    Space* getSpace() const;
    GameSession* getGameSession() const;
    virtual void Initialize() = 0;
    virtual void Terminate() = 0;
    // Utility
    SZE_DEFINE_PROPERTY(Zilch::Handle, Handle);
    static ComponentPtr Dereference(const ComponentHandle& handle);
    static std::vector<Zilch::BoundType*> All();
    // Serialization
    void Serialize(Zilch::JsonBuilder& builder);
    void Deserialize(Zilch::JsonValue* properties);
  };



}