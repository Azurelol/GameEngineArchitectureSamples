#pragma once

// Tracing, for debugging
#include "Trace.h"

// Headers
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <unordered_map>

// This macro creates the definitions of getter and setter method for a Property.
#define DEFINE_PROPERTY(propertyType, propertyName)                           \
  const propertyType& get##propertyName() const {                                 \
    return propertyName;                                                          \
  }                                                                               \
  void set##propertyName(propertyType const& value) {                             \
    propertyName = value;                                                         \
  }
// This macro creates the definitions of a getter method for a Property.
#define DEFINE_GETTER(propertyType, propertyName)                             \
  const propertyType& get##propertyName() const {                                 \
    return propertyName;                                                          \
  }
// This macro creates the definitions of a setter method for a Property.
#define DEFINE_SETTER(propertyType, propertyName)                             \
  void set##propertyName(propertyType const& value) {                             \
    propertyName = value;                                                         \
  }

// Aliases
using String = std::string;

// Base class
class Object {
  String Name;
public:
  Object(String name) : Name(name) {}
  DEFINE_GETTER(String, Name);

};
