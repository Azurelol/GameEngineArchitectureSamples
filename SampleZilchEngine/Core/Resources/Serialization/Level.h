/*****************************************************************************/
/*!
@file   Level.h
@author Christian Sagel
@par    email: c.sagel\@digipen.edu
@date   4/25/2016
@brief  A level is a resource that stores a set of GameObjects that can be loaded
        into a space.
*/
/******************************************************************************/
#pragma once
#include "..\ResourceReference.h"

namespace SZEngine {

  // Aliases
  //---------------------------------------------------------------------------/
  class Level;
  using LevelPtr = std::shared_ptr<Level>;
  //---------------------------------------------------------------------------/

  class Level : public Resource {
  public:
    Level(const std::string& name, const std::string& data);
    static LevelPtr Find(const std::string& name);
    static std::string Extension() { return ".Level"; }

  };

}