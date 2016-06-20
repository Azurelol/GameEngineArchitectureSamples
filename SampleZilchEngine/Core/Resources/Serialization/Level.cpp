/*****************************************************************************/
/*!
@file   Level.cp
@author Christian Sagel
@par    email: c.sagel\@digipen.edu
@date   4/25/2016
@brief  A level is a resource that stores a set of GameObjects that can be loaded
into a space.
*/
/******************************************************************************/
#include "Level.h"

namespace SZEngine {

  Level::Level(const std::string & name, const std::string & data) : Resource(name, data)
  {
  }

  LevelPtr Level::Find(const std::string & name)
  {
    // Look for a pointer to the level in the engine's content system
    return LevelPtr();
  }


}

