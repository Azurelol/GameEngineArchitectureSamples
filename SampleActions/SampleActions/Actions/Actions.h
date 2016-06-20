#pragma once

#include "Action\ActionCall.h"
#include "Action\ActionDelay.h"
#include "Action\ActionSequence.h"
#include "Action\ActionGroup.h"
#include "Action\ActionProperty.h"
#include "ActionSpace.h"

/**************************************************************************/
/*!
@class Actions Interface class that the client will be using for constructing 
       and interacting with actions.
*/
/**************************************************************************/
class Actions {
public:
  static bool Trace;
  // Action Sets
  static ActionSet::Ptr Sequence(ActionSet& owner);
  static ActionSet::Ptr Group(ActionSet& owner);
  // Delay
  static void Delay(ActionSet::Ptr set, float duration);
  // Call
  template <typename Class, typename... Args> static void Call(ActionSet::Ptr sets,
    void(Class::*func)(Args...), Class* object, Args...);
  // Properties: Since different types use different algorithms, we will be explicit
  static void Property(ActionSet::Ptr set, Boolean& prty, Boolean val, Real duration, Ease ease);
  static void Property(ActionSet::Ptr set, Integer& prty, Integer val, Real duration, Ease ease);
  static void Property(ActionSet::Ptr set, Real& prty, Real val, Real duration, Ease ease);
  static void Property(ActionSet::Ptr set, Vec2& prty, Vec2 val, Real duration, Ease ease);
  static void Property(ActionSet::Ptr set, Vec3& prty, Vec3 val, Real duration, Ease ease);
  static void Property(ActionSet::Ptr set, Vec4& prty, Vec4 val, Real duration, Ease ease);

};

// Temmplates
#include "Actions.hpp"
