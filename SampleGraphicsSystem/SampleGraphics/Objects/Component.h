/*****************************************************************************/
/*!
\file   Component.h
\author Christian Sagel
\par    email: c.sagel\@digipen.edu
\date   4/17/2016
\brief  The base component class.
*/
/******************************************************************************/
#pragma once
#include "Object.h"

// Forward declarations
class Entity;
class Space;
class GameObject;

class Component : public Object {
  Entity* OwnerRef;
  Space* SpaceRef;

public:
  using Ptr = Component*;
  using Container = std::vector<Ptr>;

  Component(std::string name, Entity* owner);
  void PostConstructor();
  virtual ~Component() {}
  Entity* Owner() { return OwnerRef; }
  Space* getSpace() { return SpaceRef; }
  virtual void Initialize() = 0;
  virtual void Terminate() = 0;
};



