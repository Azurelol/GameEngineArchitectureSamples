#pragma once
#include "ActionSet.h"

/**************************************************************************/
/*!
@class An ActionGroup is a type of set that updates all its actions and
children in parallel, giving each an equal time slice.
*/
/**************************************************************************/
class ActionGroup : public ActionSet {
public:
  ActionGroup() : ActionSet("ActionGroup") {}

  /**************************************************************************/
  /*!
  @brief  Updates an ActionGroup, by updating the actions in the group in
          parallel.
  @param  dt The time to be updated.
  @return How much time was consumed while updating.
  */
  /**************************************************************************/
  float Update(float dt) {

    float mostTimeElapsed = 0;

    // In an ActionGroup, every action is updated in parallel, given the same 
    // time slice.
    for (auto& action : ActiveActions) {
      auto timeElapsed = action->Update(dt);
      // If this action took longer than the previous action, it is the new maximum
      if (timeElapsed > mostTimeElapsed)
        mostTimeElapsed = timeElapsed;
      // If the action was completed (Meaning that it was completed in less time
      // than the time slice given)
      if (timeElapsed <= dt) {
        // Mark the action to be cleared
        InactiveActions.push_back(action);
      }
    }

    // Sweep all inactive actions
    Clear();
    // Validate for remaining actions
    Validate();
    // The time consumed while updating was the maximum time it took
    return mostTimeElapsed;
  }
};
