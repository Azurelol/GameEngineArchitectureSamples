#pragma once

// STL
#include <memory>
#include <vector>

// Forward declarations
class Entity;
class EventInterface;

class Component {
  friend class EventInterface;

  // When a component subscribes to an entity for events, a delegate is constructed
  // and held by that entity. For cleanup purposes we need to hold a list of all delegates
  // currently pointing at this component somewhere so that when this component is destroyed
  // we can de-register those delegates. (So that when they are invoked they don't call a null
  // object)
  using DelegateHolders = std::vector<Entity*>;
  DelegateHolders ActiveDelegateHolders;

protected:
  Entity* Owner;

public:
  // Aliases
  using Ptr = Component*;
  using StrongPtr = std::unique_ptr<Component>;
  using Container = std::vector<StrongPtr>;  

  void setOwner(Entity* owner) {
    Owner = owner;
  }

  virtual ~Component();
  virtual void Initialize() = 0;


};