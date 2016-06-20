#include "ActionSpace.h"

bool ActionSpace::Trace = false;

/**************************************************************************/
/*!
@brief ActionSpace constructor.
*/
/**************************************************************************/
ActionSpace::ActionSpace()
{
}

/**************************************************************************/
/*!
@brief ActionSpace destructor.
*/
/**************************************************************************/
ActionSpace::~ActionSpace()
{
  AllActions.clear();
}

/**************************************************************************/
/*!
@brief Adds an action onto the ActionSpace so that it can be updated.
@param action A pointer to the action.
*/
/**************************************************************************/
void ActionSpace::Add(Action::Ptr action)
{
  if (ActionSpace::Trace)
    std::cout << __FUNCTION__ << ": Adding '" << action->Type << "'\n";

  AllActions.push_back(action);
}

/**************************************************************************/
/*!
@brief Removes an action from the ActionSpace.
@param action A pointer to the action.
*/
/**************************************************************************/
void ActionSpace::Remove(Action::Ptr action)
{
  if (ActionSpace::Trace)
    std::cout << __FUNCTION__ << ": Removing '" << action->Type << "'\n";

  auto actioniter = std::find(AllActions.begin(), AllActions.end(), action);
  AllActions.erase(actioniter);
}

/**************************************************************************/
/*!
@brief Updates the ActionSpace, updating every active action.
@param dt The time slice given.
*/
/**************************************************************************/
void ActionSpace::Update(float dt)
{

  //for (size_t i = 0; i < AllActions.size(); ++i) {
  //  // If it's paused, do not update its actions
  //  if (AllActions[i]->IsPaused())
  //    continue;

  //  // Update the action
  //  AllActions[i]->Update(dt);
  //}

  for (auto& action : AllActions) {
    // If it's paused, do not update its actions
    if (action->IsPaused())
      continue;
    // Update the action
    action->Update(dt);
  }

  // Clean up any inactive actions (finished, stopped)
  Sweep();
}

/**************************************************************************/
/*!
@brief Removes all inactive actions.
*/
/**************************************************************************/
void ActionSpace::PropagateThroughOwners(float dt)
{
  for (auto& actionOwner : AllActionOwners) {

    // If it's paused, do not update its actions
    if (actionOwner->IsPaused())
      continue;

    // Update the action
    actionOwner->Update(dt);
  }
}

/**************************************************************************/
/*!
@brief Removes all inactive actions.
*/
/**************************************************************************/
void ActionSpace::Sweep()
{
}