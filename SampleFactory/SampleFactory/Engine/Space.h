#pragma once
#include "Entity.h"

#include "GameObject.h"

class Space : public Entity {

  GameObject::Container ActiveGameObjects;

  //---Suggested members-------------------------------------------------------
  // Level::Ptr CurrentLevel; // You would have a reference to the current level
  // that this space has loaded (The resource manager would own that resource!)

public:
  //---------------------------------------------------------------------------/
  // Weak:   To be shared and freely passed around.
  using Ptr = Space*;
  using Container = std::vector<Ptr>;
  // Strong: To be used when allocating components yourself, 
  //         for example with through a component factory
  using StrongPtr = std::unique_ptr<Space>;
  using StrongContainer = std::vector<StrongPtr>;
  //---------------------------------------------------------------------------/  
  Space(const std::string& name);
  void Destroy();
  void DestroyAll();

  GameObject::Ptr CreateGameObject(const std::string& name);
  void RemoveGameObject(GameObject::Ptr);
  GameObject::Container& AllGameObjects();

  //---Suggested members-------------------------------------------------------
  // void LoadLevel(LevelPtr level); // You would load a level (a serialized representation
  // of gameobjects which get instantiated on this space all at once)

};

