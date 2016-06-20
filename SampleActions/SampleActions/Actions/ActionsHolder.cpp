#include "ActionsHolder.h"

// SampleInterface / Action System singleton.:
// We will be registering our actions to it so that they are updated
// @todo Would prefer a better design pattern.
#include "..\SampleInterface.h"

ActionsHolder::ActionsHolder(Entity & owner) : ActionSet("ActionsHolder"), Owner(owner)
{
  // Sign up to the action interface
  Register();
}

ActionsHolder::~ActionsHolder()
{
  // Clean up all actions
  ActiveActions.clear();
  // Sign off the action interface
  Deregister();
}

/**************************************************************************/
/*!
@brief Updates an entity's actions. Updating all the actions one tier below
       in parallel.
@param dt The time to be updated.
@return How much time was consumed while updating.
*/
/**************************************************************************/
float ActionsHolder::Update(float dt)
{
  float mostTimeElapsed = 0;

  // In an ActionGroup, every action is updated in parallel, given the same 
  // time slice.
  //for (size_t i = 0; i < ActiveActions.size(); ++i) {
  //  auto timeElapsed = ActiveActions[i]->Update(dt);
  //  // If this action took longer than the previous action, it is the new maximum
  //  if (timeElapsed > mostTimeElapsed)
  //    mostTimeElapsed = timeElapsed;
  //  // If the action was completed (Meaning that it was completed in less time
  //  // than the time slice given)
  //  if (timeElapsed <= dt && ActiveActions[i]->Finished()) {
  //    // Mark the action to be cleared
  //    InactiveActions.push_back(ActiveActions[i]);
  //  }
  //}

  for (auto& action : ActiveActions) {
    auto timeElapsed = action->Update(dt);
    // If this action took longer than the previous action, it is the new maximum
    if (timeElapsed > mostTimeElapsed)
      mostTimeElapsed = timeElapsed;
    // If the action was completed (Meaning that it was completed in less time
    // than the time slice given)
    if (timeElapsed <= dt && action->Finished()) {
      // Mark the action to be cleared
      InactiveActions.push_back(action);
    }
  }

  // Sweep all inactive actions
  Clear();
  // The time consumed while updating was the maximum time it took
  return mostTimeElapsed;
}

/**************************************************************************/
/*!
@brief An entity's actions are never finished!
*/
/**************************************************************************/
bool ActionsHolder::Validate()
{
  return false;
}

void ActionsHolder::Register()
{
  Interface->Register(this);
}

void ActionsHolder::Deregister()
{
  Interface->Deregister(this);
}
