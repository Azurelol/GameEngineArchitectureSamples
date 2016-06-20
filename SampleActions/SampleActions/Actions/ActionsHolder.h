#pragma once
#include "Action\ActionSet.h"

/**************************************************************************/
/*!
@class An ActionOwner is a container of all actions a particular entity
has. They propagate updates to all actions attached to it.
*/
/**************************************************************************/
class Entity;
class ActionsHolder : public ActionSet {
public:
  ActionsHolder(Entity& owner);
  ~ActionsHolder();
  float Update(float dt);
  bool Validate();

  using Ptr = std::shared_ptr<ActionsHolder>;
  using Container = std::vector<Ptr>;

private:
  Entity& Owner;
  void Register();
  void Deregister();

};