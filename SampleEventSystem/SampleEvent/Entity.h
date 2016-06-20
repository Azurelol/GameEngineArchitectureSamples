#pragma once

#include "EventDelegate.h"
#include "Event.h"
#include "Component.h"

// Forward declarations
class EventInterface;

class Entity {
  friend class EventInterface;

  // Containers of delegates. We only need use one but for demonstration
  // purposes, I am demonstrating how to use both: by type and by string.
  EventDelegate::RegistryMapString ObserversByStr;
  EventDelegate::RegistryMapTypeIndex ObserversByType;

public:    
  
  // Aliases
  using Ptr = Entity*;

  // Container of components. In this sample we are just going to do it
  // quick and dumb, rather than using a component factory.
  Component::Container ActiveComponents;

  // Providing several ways to dispatch an event onto an entity depending
  // on how you have decided to sort them, using the event's name or its type

  /**************************************************************************/
  /*!
  @brief Dispatches an event to this entity by string
  @param eventObj The event object.
  */
  /**************************************************************************/
  void Dispatch(Event* eventObj) {
    // For every delegate in the registry
    for (auto& event : ObserversByStr) {
      if (eventObj->Name == event.first) {
        // For every delegate in the list for this specific event
        for (auto& deleg : event.second) {
          deleg->Call(eventObj);
        }
      }
    }
  }

  /**************************************************************************/
  /*!
  @brief Dispatches an event to this entity by type
  @param eventObj The event object that is being passed.
  */
  /**************************************************************************/
  template <typename EventClass> void Dispatch(Event* eventObj) {
    // Get the type of the given event
    auto eventType = std::type_index(typeid(EventClass));

    // Look for a match for the event type
    for (auto& eventKey : ObserversByType) {
      if (eventType == eventKey.first) {
        // If a match has been found, invoke the callback method
        // with the given event object for every delegate
        for (auto& deleg : eventKey.second) {
          deleg->Call(eventObj);
        }
      }
    }
  }

  /**************************************************************************/
  /*!
  @brief  Unsubscribes a member's function to an engine event.
  @param  entity A pointer to the engine instance.
  @param  observer A member function from the component.
  */
  /**************************************************************************/
  void Disconnect(Component* observer) {

    // 1. Look for the observer in the registry by type
    for (auto& event : ObserversByType) {
      // For every delegate in the list of delegates
      for (auto it = event.second.begin(); it != event.second.end(); ++it) {
        // If the observer the delegate is pointing to matches..
        if ((*it)->Observer() == observer) {
          event.second.erase(it);
          break;
        }
      }
    }
    // 2. Look for the observer in the second registry by name
    for (auto& event : ObserversByStr) {
      // For every delegate in the list of delegates
      for (auto it = event.second.begin(); it != event.second.end(); ++it) {
        // If the observer the delegate is pointing to matches..
        if ((*it)->Observer() == observer) {
          event.second.erase(it);
          break;
        }
      }
    }

  }

};