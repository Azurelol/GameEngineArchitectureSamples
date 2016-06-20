#include "Entity.h"

// Factory
#include "../Factory/Factory.h"

/**************************************************************************/
/*!
@brief Entity constructor.
@param name The name of the entity.
*/
/**************************************************************************/
Entity::Entity(std::string name) : Object(name)
{
}

/**************************************************************************/
/*!
@brief  Entity destructor.
*/
/**************************************************************************/
Entity::~Entity()
{
  RemoveAllComponents();
}

/**************************************************************************/
/*!
@brief  Adds a component onto the entity by name.
@param  name The name of the component.
@bool   Whether to initialize the component.
@return A pointer to the component.
*/
/**************************************************************************/
Component::Ptr Entity::AddComponent(const std::string & name, bool init)
{
  TraceObject("Adding '" + name + "'");
  // Request the object factory to construct the component
  auto component = Systems::FactoryInstance->ConstructComponentByName(name, *this);
  // We have to use std::move to be able to move unique_ptrs around
  ActiveComponents.emplace_back(std::move(component));
  // If its meant to be initialized, do so right away
  if (init)
    ActiveComponents.back()->Initialize();
   
  return ActiveComponents.back().get();
}

/**************************************************************************/
/*!
@brief  Removes the specified component from the entity.
@param  name The name of the component
@return True if the component was removed, false otherwise.
*/
/**************************************************************************/
bool Entity::RemoveComponent(const std::string & name)
{
  TraceObject("Removing '" + name + "'");
  // Factory-owned components
  for (auto& component : ActiveComponents) {
    if (component->Name == name) {
      // Call it's terminate method
      component->Terminate();
      // Remove it
      std::swap(component, ActiveComponents.back());
      ActiveComponents.pop_back();
      return true;
    }
  }
  return false;
}

/**************************************************************************/
/*!
@brief  Removes the specified component from the entity.
@param  component A pointer to the component.
@return True if the component was removed, false otherwise.
*/
/**************************************************************************/
bool Entity::RemoveComponent(Component::Ptr componentPtr)
{
  // Factory-owned components
  for (auto& component : ActiveComponents) {
    if (component.get() == componentPtr) {
      // Call it's terminate method
      component->Terminate();
      // Remove it
      std::swap(component, ActiveComponents.back());
      ActiveComponents.pop_back();
      return true;
    }
  }
  return false;
}

/**************************************************************************/
/*!
@brief  Returns a container of pointers to the components this entity owns.
@return A container of component pointers.
*/
/**************************************************************************/
Component::Container Entity::AllComponents()
{
  // Fill the container of pointers to the components that this entity owns
  Component::Container components;
  for (auto& component : ActiveComponents) {
    components.push_back(component.get());
  }
  return components;
}

/**************************************************************************/
/*!
@brief  Removes all components from the entity.
*/
/**************************************************************************/
void Entity::RemoveAllComponents()
{
  TraceObject("");
  // C++- Factory-made components
  for (auto& component : ActiveComponents) {
    component->Terminate();
  }
  ActiveComponents.clear();

}