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

namespace SPEngine
{
  class Object 
  {
    String Name;    
    unsigned ObjectID; // Unique identifier for the object
    static unsigned Created; // An incremented amount of how many objects have been created

  public:
    Object(std::string name);
    virtual ~Object();
    SP_DEFINE_PROPERTY(String, Name);

  };
}