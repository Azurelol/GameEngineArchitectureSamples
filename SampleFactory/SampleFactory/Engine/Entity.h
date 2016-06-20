#pragma once
#include "Object.h"

#include "Component.h"

class Entity : public Object {

  // Members
  std::string Archetype;
  Component::StrongContainer ActiveComponents;

public:

  Entity(std::string name);
  ~Entity();
  virtual void Destroy() {}
  // Components
  Component::Ptr AddComponent(const std::string& name, bool initialize = false);
  bool RemoveComponent(const std::string& name);
  bool RemoveComponent(Component::Ptr);
  void RemoveAllComponents();
  Component::Container AllComponents();

};






