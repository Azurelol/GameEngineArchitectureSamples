/*****************************************************************************/
/*!
\file   Object.cpp
\author Christian Sagel
\par    email: c.sagel\@digipen.edu
\date   4/17/2016
\brief  The base object class, from which everything else is derived.
*/
/******************************************************************************/
#include "Object.h"

namespace SPEngine
{
  // Statics
  unsigned Object::Created = 0;

  /**************************************************************************/
  /*!
  @brief  Object constructor.
  @param  name The name of the Object.
  @note   Every object in the engine derives from this Object, thus they all
  set their names through this constructor.
  */
  /**************************************************************************/
  Object::Object(std::string name) : Name(name), ObjectID(Created++)
  {
    //SPTraceV("Name: '" + name + "', ID: '" + std::to_string(ObjectID) + "'");
  }

  /**************************************************************************/
  /*!
  @brief  Object destructor.
  */
  /**************************************************************************/
  Object::~Object()
  {
  }

}