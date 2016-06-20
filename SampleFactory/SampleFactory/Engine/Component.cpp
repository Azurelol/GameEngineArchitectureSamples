#include "Component.h"

#include "../Factory/Factory.h"

Component::Component(std::string name, Entity & owner) : Object(name), OwnerRef(&owner)
{
  TraceObject("");
}

Entity * Component::Owner() const
{
  return OwnerRef;
}

Space * Component::getSpace() const
{
  return SpaceRef;
}

void Component::Destroy()
{
  TraceObject("");
  Systems::FactoryInstance->Destroy(this);
}
