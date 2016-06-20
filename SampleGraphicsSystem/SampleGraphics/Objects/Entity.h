/*****************************************************************************/
/*!
\file   Entity.h
\author Christian Sagel
\par    email: c.sagel\@digipen.edu
\date   4/17/2016
\brief  The base object composition class.
*/
/******************************************************************************/
#pragma once
#include "Object.h"

// Components
#include "Component.h"

#include <typeindex> // getComponent

class Entity : public Object {

  Component::Container ActiveComponents;
public:
  Entity(std::string name) : Object(name) {}

  // You are probably thinking this is stupid.. because it is!
  Component::Ptr AddComponent(Component::Ptr component) {
    ActiveComponents.push_back(component);
    return component;
  }
     
  template<typename ComponentClass>
  ComponentClass * getComponent()
  {
    // Iterate through the container of component pointers...
    for (auto &component: ActiveComponents) {
      // If the component was found
      if (std::type_index(typeid(*component)) == std::type_index(typeid(ComponentClass)))
        return (reinterpret_cast<ComponentClass*>(component));
    }

    // No matching component was found
    return nullptr;
  }

};