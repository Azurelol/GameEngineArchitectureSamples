#pragma once
#include "Object.h"


class System : public Object {
public:
  System(const std::string& name) : Object(name) {}
  using StrongPtr = std::shared_ptr<System>;
  virtual void Initialize() = 0;
  virtual void Update(float dt) = 0;
  virtual void Terminate() = 0;
};