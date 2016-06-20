#pragma once

// Normally a Trace header would be included in the precompiled header!
#include "Trace.h"

class System {

  std::string Name;

public:
  System(const std::string& name) : Name(name) {}
  virtual void Initialize() = 0;
  virtual void Update(float dt) = 0;
  virtual void Terminate() = 0;

};