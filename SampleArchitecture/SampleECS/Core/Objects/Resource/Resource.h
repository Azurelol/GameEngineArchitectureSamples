/*****************************************************************************/
/*!
@file   Resource.h
@author Christian Sagel
@par    email: c.sagel\@digipen.edu
@date   5/16/2015
@brief  Resources are the source data of a game. They are assets such as textures,
        sounds, levels, scripts. They are the resources found in a library window.
*/
/******************************************************************************/
#pragma once
#include "..\Object.h"

namespace SPEngine {

  class Resource : public Object {
  public:
    
    using Ptr = Resource*;
    using StrongPtr = std::shared_ptr<Resource>;

    Resource(std::string name, std::string resourcePath);    
    // Note: Your default serialization routines
    void Serialize();
    void Deserialize();
    // Called when you want to build the resource's serialized data
    std::string Build();
    // Saves the resource's serialized data (by writing to a file)
    virtual bool Save() = 0;
    // Loads a resource's serialized data (by reading from a file)
    virtual bool Load() = 0;

  protected:
    // The path of the file containing the resource on disk
    std::string Path;
    // The path of the asset this resource is pointing to. Note that not
    // all resources have external assets that they use. However since resources
    // are finite I am okay with paying the cost of an extraneous string in
    // a few resources than having to manually add it to most of them.
    std::string AssetPath;
    // The serialized data of the resource (Think of a BIG string, such as JSON)
    // This is not passed in the constructor since we want to have flexibility
    // when it comes to deciding when to serialize or deserialize.
    std::string SerializedData;
    bool Hidden;

  };


}