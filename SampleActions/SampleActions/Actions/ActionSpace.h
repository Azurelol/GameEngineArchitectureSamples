#pragma once
#include "ActionsHolder.h"

/**************************************************************************/
/*!
@class ActionSpace Manages the updating of all actions.
*/
/**************************************************************************/
class ActionSpace {
public:

  static bool Trace;
  void Add(Action::Ptr action);  
  void Remove(Action::Ptr action);

  void Update(float dt);

  ActionSpace();
  ~ActionSpace();

private:

  // Update methods
  void PropagateDirectly(float dt);
  void PropagateThroughOwners(float dt);
  void Sweep();
  ActionsHolder::Container AllActionOwners;
  Action::Container AllActions;
  Action::Container InactiveActions;
};
