#include "Space.h"

#include "../Factory/Factory.h"

Space::Space(const std::string & name) : Entity(name)
{
  TraceObject("");
}

void Space::Destroy()
{
  // Destroy all GameObjects on this space when this space is being destroyed
  DestroyAll();
}

void Space::DestroyAll()
{
  // Request each object to destroy itself. This will in turn request
  // the factory to destroy them on the next frame.
  for (auto& object : ActiveGameObjects) {
    object->Destroy();
  }

  ActiveGameObjects.clear();

}

GameObject::Ptr Space::CreateGameObject(const std::string & name)
{
  TraceObject(name);
  // Request the factory to construct the GameObject
  auto gameObject = Systems::FactoryInstance->ConstructGameObject(name, *this, true);
  // Add it to the container in the space
  ActiveGameObjects.push_back(gameObject);

  return gameObject;
}

void Space::RemoveGameObject(GameObject::Ptr object)
{
  // Remove the GameObject from the space's list of GameObjects
  // using 'swap and pop' technique
  for (auto gameObjPtr : ActiveGameObjects) {
    if (gameObjPtr == object) {
      std::swap(gameObjPtr, ActiveGameObjects.back());
      ActiveGameObjects.pop_back();
      TraceObject("Removed " + object->Name + " from the space.");
      break;
    }
  }

  // Request the factory to destroy this GameObject on the next frame
  Systems::FactoryInstance->Destroy(object);

}

GameObject::Container & Space::AllGameObjects()
{
  return ActiveGameObjects;
}
