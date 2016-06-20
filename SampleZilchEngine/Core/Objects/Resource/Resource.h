/*****************************************************************************/
/*!
@file   Resource.h
@author Christian Sagel
@par    email: c.sagel\@digipen.edu
@date   4/25/2016
@brief  Resources are the source data of a game. They are assets such as textures,
        sounds, levels, scripts. They are the resources found in a library window.
*/
/******************************************************************************/
#pragma once
#include "..\Object.h"

namespace SZEngine {
  
  class Resource : public Object {

    std::string Path;
    std::string SerializedData;

  public:
    ZilchDeclareDerivedType(Resource, Object);
    Resource(const std::string& name, const std::string& resourcePath);    
    virtual void Save();
    virtual void Load();
    SZE_DEFINE_PROPERTY(std::string, Path);
    
  };

  // Aliases
  using ResourcePtr = Resource*;

}