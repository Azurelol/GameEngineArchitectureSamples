#pragma once

// Tracing, for debugging
#include "Trace.h"
// Headers
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

// Base class
class Object {  
public:
  std::string Name;
  Object(std::string name) : Name(name) {}

};



