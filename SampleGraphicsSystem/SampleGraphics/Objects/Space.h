/******************************************************************************/
/*!
@file   Space.h
@author Christian Sagel
@par    email: c.sagel\@digipen.edu
@date   4/24/2016
@brief  Spaces are containers for game objects. When a level is loaded into
        a space, all the game objects from that level are put into the space.
        Each space has its own instances of interfaces to systems to the engine.
*/
/******************************************************************************/
#pragma once
#include "Entity.h"

// GameObjects
#include "GameObject.h"

class Space : public Entity {

public:

  Space(const std::string& name) : Entity(name) {}  
  Space* getSpace() { return this; }
  GameObject::Container ActiveGameObjects;

};

