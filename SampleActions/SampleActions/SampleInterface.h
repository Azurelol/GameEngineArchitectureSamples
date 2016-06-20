#pragma once

#include "Actions\Actions.h"

#include <memory>
class SampleInterface;
extern std::unique_ptr<SampleInterface> Interface;

// A sample interface for the Action system. This should be a singleton.
// In my case, I ended up integrating it directly into my engine class.
class SampleInterface {

public:
  ActionSpace ActionSpace;

  void Register(Action::Ptr action) {
    this->ActionSpace.Add(action);
  }

  void Deregister(Action::Ptr action) {
    this->ActionSpace.Remove(action);
  }

  void Update(float dt) {
    // Update all actions
    this->ActionSpace.Update(dt);
  }



};
