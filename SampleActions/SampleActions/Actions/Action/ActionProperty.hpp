#pragma once
#include "ActionProperty.h"


/**************************************************************************/
/*!
@brief ActionProperty constructor.
@param PropertyType The POD or class type of the property;
@param set A reference to the set this property is part of.
@param property A reference to the property to be modified.
@param value The new value to interpolate over the given duration.
@param duration How long this property runs for.
@param ease What ease this property uses to calculate the interpolation.
*/
/**************************************************************************/
template<typename PropertyType>
ActionFloatProperty<PropertyType>::ActionFloatProperty(ActionSet::Ptr set, PropertyType & prop,
  PropertyType value, Real duration, Ease ease)
  : ActionProperty(set, duration, ease), Property(prop), InitialValue(prop), EndValue(value)
{
  if (ActionProperty::Trace)
    std::cout << __FUNCTION__ << std::endl;

  // Initialize the rest of the values
  Difference = EndValue - InitialValue;
}

/**************************************************************************/
/*!
@brief Updates the ActionProperty.
@param dt The time slice given.
*/
/**************************************************************************/
template<typename PropertyType>
float ActionFloatProperty<PropertyType>::Interpolate(float dt)
{
  Elapsed += dt;
  auto timeLeft = Duration - Elapsed;

  if (ActionProperty::Trace)
    std::cout << __FUNCTION__ << ": dt = '" << dt << "', timeLeft = '" << timeLeft << "' \n";

  // Return the time consumed from this action. 
  auto timeConsumed = 0.0f;
  // If finished...
  if (timeLeft <= dt) {
    if (ActionProperty::Trace)
      std::cout << __FUNCTION__ << ": Finished! \n";
    timeConsumed = dt;
    IsFinished = true;
    // Set the final value
    Property = EndValue;
  }
  else {
    timeConsumed = timeLeft;
    // Set the new value
    Property = InitialValue + Difference * Easing::Calculate((Elapsed / Duration), EaseType);
  }

  return timeConsumed;
}

/**************************************************************************/
/*!
@brief ActionBooleanProperty constructor.
@param set A pointer to the set this action belongs to.
@param prop A reference to the property.
@param value The desired end value for the property.
@param duration The duration of this action.
@param ease What ease algorithm to use.
*/
/**************************************************************************/
template<typename BooleanType>
ActionBooleanProperty<BooleanType>::ActionBooleanProperty(ActionSet::Ptr set, BooleanType & prop, BooleanType value, Real duration, Ease ease)
  : ActionProperty(set, duration, ease), Property(prop), EndValue(value)
{
}

/**************************************************************************/
/*!
@brief Updates the ActionProperty.
@param dt The time slice given.
*/
/**************************************************************************/
template<typename BooleanType>
inline float ActionBooleanProperty<BooleanType>::Interpolate(float dt)
{
  Elapsed += dt;
  auto timeLeft = Duration - Elapsed;

  if (ActionProperty::Trace)
    std::cout << __FUNCTION__ << ": dt = '" << dt << "', timeLeft = '" << timeLeft << "' \n";

  // Return the time consumed from this action. 
  auto timeConsumed = 0.0f;
  if (timeLeft <= dt) {
    if (ActionProperty::Trace)
      std::cout << __FUNCTION__ << ": Finished! \n";
    IsFinished = true;
    timeConsumed = dt;
    // Set the boolean value only at the end!
    Property = EndValue;
  }
  else
    timeConsumed = timeLeft;

  return timeConsumed;
}