/*****************************************************************************/
/*!
@file   Resource.cpp
@author Christian Sagel
@par    email: c.sagel\@digipen.edu
@date   5/16/2015
@brief  Resources are the source data of a game. They are assets such as textures,
sounds, levels, scripts. They are the resources found in a library window.
*/
/******************************************************************************/
#include "Resource.h"

namespace SPEngine {

  /**************************************************************************/
  /*!
  @brief  Resource constructor.
  @param  name The name of the Resource.
  @param  path The path of the file containing the resource on disk.
  */
  /**************************************************************************/
  Resource::Resource(std::string name, std::string path) :
    Object(name), Path(path)
  {
  }

}