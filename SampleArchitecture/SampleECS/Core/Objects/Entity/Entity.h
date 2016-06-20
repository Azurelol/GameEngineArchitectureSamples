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
#include "..\Object.h"

// Components
#include "..\Component\Component.h"

namespace SPEngine {

  class Entity : public Object {

    // Members
    std::string Archetype;
    Component::StrongContainer ActiveComponents;

  public:
    
    Entity(std::string name);
    ~Entity();
    virtual void Destroy() {}
    // Components
    Component::Ptr AddComponentByName(const std::string& name, bool initialize);
    Component::Container AllComponents();
    void RemoveAllComponents();
    template <typename ComponentClass> ComponentClass* getComponent();

  };
}

// Templates
#include "Entity.hpp"