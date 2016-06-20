#pragma once
#include "Actions.h"

/**************************************************************************/
/*!
@brief Creates an ActionCall and adds it to the specified set.
@param set A reference to the set.
@param func The function to which to call.
@param object The object on which to invoke the function on.
@param ... Variadic arguments for the member function.
*/
/**************************************************************************/
template<typename Class, typename ...Args>
void Actions::Call(ActionSet::Ptr set, void(Class::* func)(Args...), Class * object, Args ...)
{
  auto deleg = new MemberFunctionDelegate<Class>(object, func);
  // Construct an ActionCall object
  Action::Ptr call(new ActionCall(set, deleg));
  // Add it to the set
  set->Add(call);
}
