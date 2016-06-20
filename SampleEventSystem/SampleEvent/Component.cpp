#include "Component.h"
#include "EventInterface.h"

Component::~Component()
{
  for (auto& entity : ActiveDelegateHolders) {
    Interface->Disconnect(entity, this);
  }
}
