/******************************************************************************/
/*!
@file   GameObject.h
@author Christian Sagel
@par    email: c.sagel\@digipen.edu
@date   4/24/2016
@brief  The Game Object composition class. 
*/
/******************************************************************************/
#pragma once
#include "Entity.h"

  // Forward declarations
  class Space;

  class GameObject : public Entity {

    Space& SpaceRef;

  public:
    //---------------------------------------------------------------------------/
    // Aliases
    using Ptr = GameObject*;
    using Container = std::vector<Ptr>;
    //---------------------------------------------------------------------------/

    GameObject(const std::string& name, Space& space) : Entity(name), SpaceRef(space) {}
    ~GameObject() {}
    Space* getSpace() { return &SpaceRef; }
  };


