#include "Actions.h"

bool ActionDelay::Trace = false;
bool ActionCall::Trace = false;
bool ActionProperty::Trace = false;
bool Actions::Trace = false;

/**************************************************************************/
/*!
@brief Creates an action sequence.
@param owner A reference to the owner of this action sequence.
*/
/**************************************************************************/
ActionSet::Ptr Actions::Sequence(ActionSet & owner)
{
  if (Trace) {
    std::cout << __FUNCTION__ << std::endl;
  }

  // Construct an action group
  ActionSet::Ptr sequence(new ActionSequence());
  // Add this action group to the set
  owner.Add(sequence);
  // Return a reference to this action group
  return sequence;
}

/**************************************************************************/
/*!
@brief Creates an action sequence.
@param owner A reference to the owner of this action sequence.
*/
/**************************************************************************/
ActionSet::Ptr Actions::Group(ActionSet & owner)
{
  if (Trace) {
    std::cout << __FUNCTION__ << std::endl;
  }

  // Construct an action group
  ActionSet::Ptr group(new ActionGroup());
  // Add this action group to the set
  owner.Add(group);
  // Return a reference to this action group
  return group;
}

/**************************************************************************/
/*!
@brief Creates an ActionDelay
@param set A reference to the ActionSet that this action belongs to.
@param duration How long should the delay run for.
*/
/**************************************************************************/
void Actions::Delay(ActionSet::Ptr set, float duration)
{
  if (Trace) {
    std::cout << __FUNCTION__ << std::endl;
  }

  // Construct the action and add it to the action set
  Action::Ptr call(new ActionDelay(set, duration));
  // Add it to the set
  set->Add(call);
}

void Actions::Property(ActionSet::Ptr set, Boolean & prty, Boolean val, Real duration, Ease ease)
{
  if (Trace) {
    std::cout << __FUNCTION__ << std::endl;
  }

  Action::Ptr prop(new ActionBooleanProperty<Boolean>(set, prty, val, duration, ease));
  set->Add(prop);
}

void Actions::Property(ActionSet::Ptr set, Integer & prty, Integer val, Real duration, Ease ease)
{
  if (Trace) {
    std::cout << __FUNCTION__ << std::endl;
  }

  Action::Ptr prop(new ActionIntegerProperty(set, prty, val, duration, ease));
  set->Add(prop);
}

void Actions::Property(ActionSet::Ptr set, Real & prty, Real val, Real duration, Ease ease)
{
  if (Trace) {
    std::cout << __FUNCTION__ << std::endl;
  }

  Action::Ptr prop(new ActionFloatProperty<Real>(set, prty, val, duration, ease));
  set->Add(prop);

}

void Actions::Property(ActionSet::Ptr set, Vec2 & prty, Vec2 val, Real duration, Ease ease)
{
  if (Trace) {
    std::cout << __FUNCTION__ << std::endl;
  }

  Action::Ptr prop(new ActionFloatProperty<Vec2>(set, prty, val, duration, ease));
  set->Add(prop);

}

void Actions::Property(ActionSet::Ptr set, Vec3 & prty, Vec3 val, Real duration, Ease ease)
{
  if (Trace) {
    std::cout << __FUNCTION__ << std::endl;
  }

  Action::Ptr prop(new ActionFloatProperty<Vec3>(set, prty, val, duration, ease));
  set->Add(prop);
}

void Actions::Property(ActionSet::Ptr set, Vec4 & prty, Vec4 val, Real duration, Ease ease)
{
  if (Trace) {
    std::cout << __FUNCTION__ << std::endl;
  }

  Action::Ptr prop(new ActionFloatProperty<Vec4>(set, prty, val, duration, ease));
  set->Add(prop);
}
