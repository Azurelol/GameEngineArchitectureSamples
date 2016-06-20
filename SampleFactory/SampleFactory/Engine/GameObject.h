#pragma once
#include "Entity.h"

// Forward declaration
class Space;

class GameObject : public Entity {
  Space& SpaceRef;
public:
  //---------------------------------------------------------------------------/
  // Weak:   To be shared and freely passed around.
  using Ptr = GameObject*;
  using Container = std::vector<Ptr>;
  // Strong: To be used when allocating components yourself, 
  //         for example with through a component factory
  using StrongPtr = std::unique_ptr<GameObject>;
  using StrongContainer = std::vector<StrongPtr>;
  //---------------------------------------------------------------------------/
  GameObject(const std::string& name, Space& space);
  void Destroy();
};