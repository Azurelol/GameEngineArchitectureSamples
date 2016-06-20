#pragma once
#include "ActionSet.h"

/**************************************************************************/
/*!
@class An ActionDelay is a type of action that blocks all actions behind it
for a specified amount of time.
*/
/**************************************************************************/
class ActionDelay : public Action {
public:

  static bool Trace;

  ActionDelay(ActionSet::Ptr set, float duration) : Action("ActionDelay") {
    Duration = duration;
  }

  float Update(float dt) {

    Elapsed += dt;
    auto timeLeft = Duration - Elapsed;
    if (Elapsed >= Duration) {
      IsFinished = true;
    }
    else {
      if (ActionDelay::Trace)
        std::cout << __FUNCTION__ << ": dt = '" << dt << "', timeLeft = '" << timeLeft << "' \n";
    }

    auto timeConsumed = 0.0f;
    if (timeLeft < dt)
      timeConsumed = dt;
    else
      timeConsumed = timeLeft;

    // Return the time consumed from this action. 
    return timeConsumed;
  }
};


