/*****************************************************************************/
/*!
\file   System.cpp
\author Christian Sagel
\par    email: c.sagel\@digipen.edu
\date   4/17/2016
\brief  The base System class, from which all of the engine's systems derive from.
*/
/******************************************************************************/
#include "System.h"

namespace SZEngine {

  System::System(std::string name) : Object(name)
  {
  }

}