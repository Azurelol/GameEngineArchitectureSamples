#include "ActionSet.h"

#include <algorithm> // remove_if

bool ActionSet::Trace = false;

/**************************************************************************/
/*!
@brief  Clears all inactive actions.
*/
/**************************************************************************/
void ActionSet::Clear()
{
  if (InactiveActions.empty())
    return;

  // Remove the action from the active actions!
  ActiveActions.erase(
    std::remove_if(ActiveActions.begin(), ActiveActions.end(),
      [&](Action::Ptr& a) {
    return std::find(
      InactiveActions.cbegin(),
      InactiveActions.cend(),
      a)
      != InactiveActions.end(); }),
    ActiveActions.end());

  // Now clear!
  if (ActionSet::Trace)
    std::cout << __FUNCTION__ << ": Removed '" << InactiveActions.size() << "' actions: \n";

  for (auto& action : InactiveActions) {
    if (ActionSet::Trace)
      std::cout << " - " << action->Type << "\n";

    delete action;
  }

  InactiveActions.clear();
}

/**************************************************************************/
/*!
@brief  Adds an ActionSet to this set, as a child set.
@param set A reference to the child set.
*/
/**************************************************************************/
void ActionSet::Add(ActionSet::Ptr set)
{
  ActiveActions.push_back(set);
}

/**************************************************************************/
/*!
@brief  Adds an Action to this set, as one of its active actions.
@param action A pointer to the other action.
*/
/**************************************************************************/
void ActionSet::Add(Action::Ptr action)
{
  ActiveActions.push_back(action);
}

/**************************************************************************/
/*!
@brief  Checks whether there are any remaining actions in the ActionSet.
If there's no more remaining, the set is done.
*/
/**************************************************************************/
bool ActionSet::Validate()
{
  if (ActiveActions.empty())
    IsFinished = true;
  return IsFinished;
}