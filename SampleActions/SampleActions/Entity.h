#pragma once

#include "Actions\ActionsHolder.h"

// Forward declaration
class Entity;

class Component {
  Entity& Owner;
  const std::string Name;
public:
  Component(const std::string& name, Entity& owner) : Name(name), Owner(owner) {}
  using Ptr = Component*;
  Entity& getOwner() { return Owner; }
  const std::string& getName() { return Name; }

};

class Entity {
public:
  std::vector<Component::Ptr> Components;
  ActionsHolder Actions;

  Entity() : Actions(*this) {}

  ~Entity() { 
    for (auto& component : Components) 
      delete component; 
    Components.clear();
  }
};
