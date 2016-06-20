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
#include "..\Object.h"

namespace SPEngine {

  //---------------------------------------------------------------------------/
  // Forward declarations
  class Entity;
  class Space;
  class GameSession;
  //---------------------------------------------------------------------------/
  class Component : public Object {
    Entity* OwnerRef;
    const Space* SpaceRef;
    const GameSession* GameSessionRef;

    void Configure();

  public:

    //---------------------------------------------------------------------------/
    // Weak:   To be shared and freely passed around.
    using Ptr = Component*;
    using Container = std::vector<Ptr>;
    // Strong: To be used when allocating components yourself, 
    //         for example with through a component factory
    using StrongPtr = std::unique_ptr<Component>;
    using StrongContainer = std::vector<StrongPtr>;
    //---------------------------------------------------------------------------/

    Component(std::string name, Entity* owner);
    Component();
    ~Component();
    void PostDefaultConstructor();

    Entity* Owner();
    Space* getSpace() const;
    GameSession* getGameSession() const;
    virtual void Initialize() = 0;
    virtual void Terminate() = 0;
  };



}