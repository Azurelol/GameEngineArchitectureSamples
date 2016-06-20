#include "GameObject.h"

#include "../Factory/Factory.h"
#include "Space.h"

GameObject::GameObject(const std::string & name, Space & space) 
  : Entity(name), SpaceRef(space)
{
  TraceObject("");
}

void GameObject::Destroy()
{
  TraceObject("");
  // Request the Space to remove this GameObject.
  SpaceRef.RemoveGameObject(this);
}
