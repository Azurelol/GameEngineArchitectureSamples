#include "Component.h"

#include "Space.h"

Component::Component(std::string name, Entity * owner) : Object(name), OwnerRef(owner) 
{
  PostConstructor();
}

// This step cannot be done in the header since we need to know the type definition
// in order to dynamic_cast
void Component::PostConstructor()
{
  if (auto gameObject = dynamic_cast<GameObject*>(OwnerRef)) {
    SpaceRef = gameObject->getSpace();
  }
  else if (auto space = dynamic_cast<Space*>(OwnerRef)) {
    SpaceRef = space;
  }
}
