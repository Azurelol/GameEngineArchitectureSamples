#include "ActionProperty.h"

//----------------------------------------------------------------------------/

ActionProperty::ActionProperty(ActionSet::Ptr set, Real duration, Ease ease)
  : Duration(duration), EaseType(ease)
{
}

float ActionProperty::Update(float dt)
{
  return Interpolate(dt);
}

//----------------------------------------------------------------------------/
// Integer
/**************************************************************************/
/*!
@brief ActionIntegerProperty constructor.
@param set A pointer to the set this action belongs to.
@param deleg The property delegate.
@param value The desired end value for the property.
@param duration The duration of this action.
@param ease What ease algorithm to use.
*/
/**************************************************************************/
ActionIntegerProperty::ActionIntegerProperty(ActionSet::Ptr set, Integer & prop, Integer value, Real duration, Ease ease)
  : ActionProperty(set, duration, ease), Property(prop), InitialValue(prop), EndValue(value)
{
  // Calculate the difference
  Difference = EndValue - InitialValue;
}

/**************************************************************************/
/*!
@brief Interpolates the property towards the intended value.
@param dt The delta time.
*/
/**************************************************************************/
float ActionIntegerProperty::Interpolate(float dt)
{
  Elapsed += dt;
  auto timeLeft = Duration - Elapsed;
  if (ActionProperty::Trace)
    std::cout << __FUNCTION__ << ": dt = '" << dt << "', timeLeft = '" << timeLeft << "' \n";

  // Calculate the interpolated value
  auto currVal = InitialValue + Difference * Easing::Calculate((Elapsed / Duration), EaseType);

  // Return the time consumed from this action. 
  auto timeConsumed = 0.0f;
  // If the action is finished
  if (timeLeft <= dt) {
    if (ActionProperty::Trace)
      std::cout << __FUNCTION__ << ": Finished! \n";
    timeConsumed = dt;
    IsFinished = true;
    Property = EndValue;
  }
  // If there is time left...
  else {
    timeConsumed = timeLeft;
    Property = std::ceil(currVal);
  }

  return timeConsumed;
}
