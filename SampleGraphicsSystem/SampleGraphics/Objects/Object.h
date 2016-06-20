/*****************************************************************************/
/*!
\file   Object.h
\author Christian Sagel
\par    email: c.sagel\@digipen.edu
\date   4/17/2016
\brief  The base object class, from which everything else is derived.
*/
/******************************************************************************/
#pragma once

// Normally these would go on a precompiled header ^.^
#include <vector>
#include <memory>
#include <unordered_map>
#include <map>

#include "Types.h"
#include "Utilities.h"


class Object
{
  std::string Name;

public:
  Object(std::string name) : Name(name) {}
  virtual ~Object() {}
  DEFINE_PROPERTY(std::string, Name);

};
