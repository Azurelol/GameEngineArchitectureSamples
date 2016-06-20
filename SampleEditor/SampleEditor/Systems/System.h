#pragma once

// Libraries
#include <memory>
#include <vector>

class System {
public:
  using StrongPtr = std::unique_ptr<System>;
  using Container = std::vector<StrongPtr>;

  virtual void Initialize() = 0;
  virtual void Terminate() = 0;
  virtual void Update(float dt) = 0;
};

#define Trace(message) std::cout << __FUNCTION__ << ": " << message << std::endl;