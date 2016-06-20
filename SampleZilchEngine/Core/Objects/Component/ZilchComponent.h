/*****************************************************************************/
/*!
@file   ZilchComponent.h
@author Christian Sagel
@par    email: c.sagel\@digipen.edu
@date   6/10/2016
@brief  Zilch components are used by gameplay programmers to write game logic into.
        These components, alongside events, drive the logic of a game project.
*/
/******************************************************************************/
#pragma once
#include "Component.h"

namespace SZEngine {
  
  class ZilchComponent : public Component {

    Zilch::ExceptionReport Report;
    void FindFunctions();
    Zilch::Function* InitializeFunc;
    Zilch::Function* TerminateFunc;
    Zilch::Function* DestroyFunc;

  public:
    ZilchDeclareDerivedType(ZilchComponent, Component);
    static bool IsA(Component::Ptr component);
    ZilchComponent();
    virtual ~ZilchComponent();
    virtual void Initialize();
    virtual void Terminate();
    // Serialization
    void Serialize(Zilch::JsonBuilder& builder);
    void Deserialize(Zilch::JsonValue* properties);

  };

}