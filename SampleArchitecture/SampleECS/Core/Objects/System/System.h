#pragma once

#include "..\Object.h"

namespace SPEngine {

  class System : public Object {
  public:
    using StrongPtr = std::unique_ptr<System>;
    using Container = std::vector<StrongPtr>;

    System(std::string systemName) : Object(systemName) {}
    virtual void Initialize() = 0;
    virtual void Terminate() = 0;
    virtual void Update(float dt) = 0;
  };  

}