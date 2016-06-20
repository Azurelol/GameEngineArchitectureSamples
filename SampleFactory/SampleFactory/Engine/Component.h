#pragma once
#include "Object.h"

//---------------------------------------------------------------------------/
// Forward declarations
class Entity;
class Space;
//---------------------------------------------------------------------------/

class Component : public Object {
  
  Entity* OwnerRef;
  Space* SpaceRef;

public:

  //---------------------------------------------------------------------------/
  // Weak:   To be shared and freely passed around.
  using Ptr = Component*;
  using Container = std::vector<Ptr>;
  // Strong: To be used when allocating components yourself, 
  //         for example with through a component factory
  using StrongPtr = std::unique_ptr<Component>;
  using StrongContainer = std::vector<StrongPtr>;
  //---------------------------------------------------------------------------/

  Component(std::string name, Entity& owner);
  virtual void Initialize() = 0;
  virtual void Terminate() = 0;
  Entity* Owner() const;
  Space* getSpace() const;
  void Destroy();
  

  template <typename T>
  T* Owner() {
    if (auto gameObject = dynamic_cast<GameObject*>(OwnerRef))
      return gameObject;
    else if (auto space = dynamic_cast<Space*>(OwnerRef))
      return space;
    return nullptr;
  }

};

