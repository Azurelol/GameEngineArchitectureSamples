/*****************************************************************************/
/*!
\file   System.h
\author Christian Sagel
\par    email: c.sagel\@digipen.edu
\date   4/17/2016
\brief  The base System class, from which all of the engine's systems derive from.
*/
/******************************************************************************/
#pragma once
#include "..\Object.h"

namespace SZEngine {

  class System : public Object {
  public:
    System(std::string name);
    virtual void Initialize() = 0;
    virtual void Update(float dt) = 0;
    virtual void Terminate() = 0;
  };

  namespace Systems {
    using SystemPtr = std::unique_ptr<System>;
    using SystemsContainer = std::vector<SystemPtr>;
  }


}