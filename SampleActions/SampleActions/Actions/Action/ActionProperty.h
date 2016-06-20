#pragma once
#include "ActionSet.h"
#include "Ease.h"

/**************************************************************************/
/*!
@class ActionBaseProperty Base property class from which the other
property classes derive from.
*/
/**************************************************************************/
class ActionProperty : public Action {
public:
  static bool Trace;
  ActionProperty(ActionSet::Ptr set, Real duration, Ease ease);
  float Update(float dt);
  virtual float Interpolate(float dt) = 0;
protected:
  Real Duration;
  Ease EaseType;
};

//----------------------------------------------------------------------------/
/**************************************************************************/
/*!
@class ActionProperty A type of action that modifies the value of
a given property over a specified amount of time, using a specified
interpolation formula (Ease).
*/
/**************************************************************************/
template <typename PropertyType>
class ActionFloatProperty : public ActionProperty {
public:
  ActionFloatProperty(ActionSet::Ptr set, PropertyType& prop, PropertyType value, Real duration, Ease ease);
  float Interpolate(float dt);

private:
  PropertyType& Property;
  PropertyType Difference;
  PropertyType InitialValue;
  PropertyType EndValue;
};

/**************************************************************************/
/*!
@class ActionZilchStringProperty Property class for String values.
*/
/**************************************************************************/
template <typename BooleanType>
class ActionBooleanProperty : public ActionProperty {
public:
  ActionBooleanProperty(ActionSet::Ptr set, BooleanType& prop, BooleanType value, Real duration, Ease ease);
  float Interpolate(float dt);
private:
  BooleanType& Property;
  BooleanType EndValue;
};

/**************************************************************************/
/*!
@class ActionZilchStringProperty Property class for String values.
*/
/**************************************************************************/
class ActionIntegerProperty : public ActionProperty {
public:
  ActionIntegerProperty(ActionSet::Ptr set, Integer& prop, Integer value, Real duration, Ease ease);
  float Interpolate(float dt);
private:
  Integer& Property;
  Integer InitialValue;
  Integer EndValue;
  Real Difference;
};

// Template definitions
#include "ActionProperty.hpp"