#pragma once
#include "ActionSet.h"
#include "Delegate.h"

/**************************************************************************/
/*!
@class An ActionCall is a type of action that invokes a function the moment
immediately after being updated.
*/
/**************************************************************************/
class ActionCall : public Action {

  Delegate* FunctionPtr;

public:
  
  static bool Trace;

  ActionCall(ActionSet::Ptr set, Delegate* funcPtr) : 
    Action("ActionCall"), FunctionPtr(funcPtr) {}

  float Update(float dt) {
    if (ActionCall::Trace)
      std::cout << __FUNCTION__ << ": Calling function \n";
    // Call the function immediately
    FunctionPtr->Call();
    this->IsFinished = true;
    // No time is consumed for ActionCalls
    return 0.0f;
  }
};