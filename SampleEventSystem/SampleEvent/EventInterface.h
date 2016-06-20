#pragma once

// Events
#include "EventDelegate.h"
#include "Event.h"
// Entity
#include "Entity.h"
// Component
#include "Component.h"

// Singleton
extern std::unique_ptr<EventInterface> Interface;

class EventInterface {

  /**************************************************************************/
  /*!
  @brief  Subscribes a component to an entity by string, registering it to its
          observers' registry for the specific event.
  @param  eventName The name of the event.
  @param  entity A pointer to the entity.
  @param  deleg The member function delegate, casted to its base class.
  @param  inst A pointer to the component.
  */
  /**************************************************************************/
  void Connect(const std::string & eventName, Entity* entity, EventDelegate * deleg, Component * inst) {
    // Store the base delegate to the <EventClass, std::list<EventDelegate*> > map
    entity->ObserversByStr[eventName].emplace_back(deleg);
    // Add a pointer to the publishing entity in the component
    inst->ActiveDelegateHolders.push_back(entity);
  }

public:

  /**************************************************************************/
  /*!
  @brief  Subscribes a component to an entity by type, registering it to its 
          observers' registry for the specific event.
  @param  entity A pointer to the entity.
  @param  func A member function from the component.
  @param  inst A pointer to the component.
  */
  /**************************************************************************/
  template <typename EventClass, typename ComponentClass, typename MemberFunction>
  void Connect(Entity* entity, MemberFunction func, ComponentClass* inst) {

    // Construct the member function delegate
    auto memberFuncDeleg = new EventMemberFunctionDelegate<ComponentClass, EventClass>();
    memberFuncDeleg->FuncPtr = func;
    memberFuncDeleg->Inst = inst;

    // Create a base delegate pointer, which will be the one stored by the entity.
    auto delegPtr = dynamic_cast<EventDelegate*>(memberFuncDeleg);

    // Store the base delegate in the entity's map container of delegates by type:
    // We are constructing a type_index object to act as the key for this map.
    entity->ObserversByType[std::type_index(typeid(EventClass))].emplace_back(delegPtr);
    
    // Register this entity as being one of the entities that the component is currently
    // listening to.

  }

  /**************************************************************************/
  /*!
  @brief  Subscribes a component to an entity by string, registering it to its
          observers' registry for the specific event.
  @param  entity A pointer to the entity.
  @param  func A member function from the component.
  @param  inst A pointer to the component.
  */
  /**************************************************************************/
  template<typename EventClass, typename Class, typename MemberFunction>
  void Connect(std::string eventName, Entity* entity, MemberFunction func, Class* inst) {

    // Construct the member function delegate
    auto memberFuncDeleg = new EventMemberFunctionDelegate<ComponentClass, EventClass>();
    memberFuncDeleg->FuncPtr = func;
    memberFuncDeleg->Inst = inst;
    // Connect by string
    Connect(eventName, entity, memberFuncDeleg, inst);
  }

  /**************************************************************************/
  /*!
  @brief  Unsubscribes a member's function to an engine event.
  @param  entity A pointer to the engine instance.
  @param  observer A member function from the component.
  */
  /**************************************************************************/
  void Disconnect(Entity* entity, Component* observer)
  {
    entity->Disconnect(observer);
  }

};
