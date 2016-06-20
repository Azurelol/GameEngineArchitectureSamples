/*****************************************************************************/
/*!
@file   Resource.cpp
@author Christian Sagel
@par    email: c.sagel\@digipen.edu
@date   4/25/2016
@brief  Resources are the source data of a game. They are assets such as textures,
sounds, levels, scripts. They are the resources found in a library window.
*/
/******************************************************************************/
#include "Resource.h"

namespace SZEngine {

  /*!************************************************************************\
  @brief  Resource Definition
  \**************************************************************************/
  ZilchDefineType(Resource, "Resource", SZEngineCore, builder, type) {
    SZE_BINDING_SET_HANDLE_TYPE_POINTER;
    // Constructor / Destructor
    ZilchBindConstructor(builder, type, Resource, "name, resourcePath", std::string, std::string);
    ZilchBindDestructor(builder, type, Resource);
    // Properties
    SZE_BINDING_DEFINE_PROPERTY(Resource, Path);

  }

  Resource::Resource(const std::string & name, const std::string & resourcePath) 
    : Object(name), Path(resourcePath)
  {
  }

  void Resource::Save()
  {
  }

  void Resource::Load()
  {
  }
}