/******************************************************************************/
/*!
@file   EventDelegate.h
@author Christian Sagel
@par    email: c.sagel\@digipen.edu
@date   5/16/2016
@brief  A delegate is a class that wraps a pointer or reference to an object
        instance, a member method of that object's class to be called on that
        object instance, and provides a method to trigger that call.
*/
/******************************************************************************/
#pragma once

// STL Libraries
#include <string>
#include <list>
#include <map>
#include <memory> // unique_ptr
#include <functional>
#include <typeindex>
#include <typeinfo>

// Forward declarations
class Event;
class Component;

/**************************************************************************/
/*!
@class EventDelegate Base class for delegates used for the event system.
*/
/**************************************************************************/
class EventDelegate {
public:
  EventDelegate() {}
  virtual ~EventDelegate() {};
  virtual bool Call(Event* event) = 0;
  virtual Component* Observer() = 0;


  // Containers: We are providing two ways to sort through events. By string
  // and by type_index. String identification is normally used when binding
  // to scripting languages.
  using List = std::list<std::unique_ptr<EventDelegate>>;  
  using RegistryMapString = std::map<std::string, List>;
  using RegistryMapTypeIndex = std::map<std::type_index, List>;

};

/**************************************************************************/
/*!
@class EventMemberFunctionDelegate Templated class that allows member
functions to connect to an entity's events. This version is used
by C++.
*/
/**************************************************************************/
template <typename Class, typename EventClass>
class EventMemberFunctionDelegate : public EventDelegate {
public:
  typedef void(Class::*EventFn)(EventClass* event);
  EventFn FuncPtr;
  Class* Inst;

  /**************************************************************************/
  /*!
  @brief  Calls the member function given an event.
  @param  A pointer to the event object.
  @note   If the Object instance is no longer valid (such as if the object
  was destroyed, this will return false)
  */
  /**************************************************************************/
  virtual bool Call(Event* event) {
    EventClass* eventObj = dynamic_cast<EventClass*>(event);
    // If the object instance has been rendered null, do nothing
    if (Inst == nullptr || FuncPtr == nullptr) {
      return false;
    }
    // Else, if it is active, dispatch the event object
    (Inst->*FuncPtr)(eventObj);
    return true;
  }

  Component* Observer() {
    return Inst;
  }


};