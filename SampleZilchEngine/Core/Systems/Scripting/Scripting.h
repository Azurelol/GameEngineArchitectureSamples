/*****************************************************************************/
/*!
\file   Scripting.h
\author Christian Sagel
\par    email: c.sagel\@digipen.edu
\date   4/20/2016
\brief  The interface to the Scripting system used by the engine (Zilch).
*/
/******************************************************************************/
#pragma once
#include "..\SystemReference.h"

// Zilch
#include "ZilchInterface\ZilchInterface.h"

namespace SZEngine {
  namespace Systems {

    class Scripting : public System
    {
      std::unique_ptr<ZilchInterface> Interface;

    public:
      Scripting();
      void Initialize();
      void Update(float dt);
      void Terminate();

    };


  }
}
