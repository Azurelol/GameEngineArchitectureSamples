#pragma once
#include "Action.h"

//----------------------------------------------------------------------------/
#include <memory>
//----------------------------------------------------------------------------/
/**************************************************************************/
/*!
@class The ActionSet is the base class from which all other sets derive.
       Sets such as Sequence, Group and the unique set used by entities.
*/
/**************************************************************************/
class ActionSet : public Action {
public:

  using Ptr = ActionSet*;

  static bool Trace;

  ActionSet(std::string type = "ActionSet") : Action(type) {}
  virtual void Add(ActionSet::Ptr set);
  virtual void Add(Action::Ptr action);
  virtual float Update(float dt) = 0;
  virtual bool Validate();

protected:
  std::vector<Action::Ptr> ActiveActions;
  std::vector<Action::Ptr> InactiveActions;
  void Clear();  
};