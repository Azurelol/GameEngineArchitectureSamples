#pragma once
#include "ActionSet.h"

/**************************************************************************/
/*!
@class An ActionSequence is a type of set that updates all its actions
and children in sequence, depleting its time slice as it updates
each.
*/
/**************************************************************************/
class ActionSequence : public ActionSet {
public:
  ActionSequence() : ActionSet("ActionSequence") {}

  /**************************************************************************/
  /*!
  @brief  Updates an ActionSequence, by updating the actions in the sequence
          sequentially.
  @param  dt The time to be updated.
  @return How much time was consumed while updating.
  */
  /**************************************************************************/
  float Update(float dt) {

    auto timeLeft = dt;
    for (auto& action : ActiveActions) {
      // Every action consume time in the time slice given.
      timeLeft -= action->Update(timeLeft);
      // If the action was completed (Meaning there is time remaining after it was updated)
      // , then mark the action to be cleared.
      if (timeLeft >= 0) {
        InactiveActions.push_back(action);
      }
      // If we have run out of time, break out of the loop!
      if (timeLeft <= 0)
        break;
    }
    // Sweep all inactive actions
    Clear();
    // Validate for remaining actions
    Validate();
    // The time was consumed while updating...
    return dt - timeLeft;
  }
};