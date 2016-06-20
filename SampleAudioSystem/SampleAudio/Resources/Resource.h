#pragma once

#include <string>
#include <memory> // shared_ptr
#include <vector>

using Real = float;
using String = std::string;

// This macro creates the definitions of getter and setter method for a Property.
#define DEFINE_PROPERTY(propertyType, propertyName)                               \
  const propertyType& get##propertyName() const {                                 \
    return propertyName;                                                          \
  }                                                                               \
  void set##propertyName(propertyType const& value) {                             \
    propertyName = value;                                                         \
  }

class Resource {

  std::string Name;
  std::string Path; // The path for the serialized data of this resource
  std::string AssetPath; // The path where the asset this resource uses is

public:
  Resource(const std::string& name) : Name(name) {}
  DEFINE_PROPERTY(std::string, Name);
  DEFINE_PROPERTY(std::string, AssetPath);

};
