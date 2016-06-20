#pragma once

#include "..\Engine\ObjectsInclude.h"
#include "ComponentFactory.h"
#include <set>

// Base class for all systems
class System : public Object {
public:
  System(const std::string& name) : Object(name) {}
  using StrongPtr = std::shared_ptr<System>;
  virtual void Initialize() = 0;
};

namespace Systems {

  class Factory : public System {
  public:
    Factory();
    void Initialize();
    void Update(float dt);
    // Construction
    Component::StrongPtr ConstructComponentByName(const std::string& name, Entity& entity);
    GameObject::Ptr ConstructGameObject(const std::string& name, Space& space, bool init);
    Space::Ptr ConstructSpace(const std::string& name, bool init);
    // Deallocation
    void Destroy(GameObject::Ptr gameObj);
    void Destroy(Space::Ptr space);
    void Destroy(Component::Ptr component);

  private:

    // Entities are owned by the factory
    Space::StrongContainer ActiveSpaces;
    GameObject::StrongContainer ActiveGameObjects;
    // Containers of marked objects to be deleted on the next frame
    Space::Container SpacesToDelete;
    GameObject::Container GameObjectsToDelete;
    Component::Container ComponentsToDelete;
    void DestroyMarkedGameObjects();
    void DestroyMarkedComponents();
    // Component factories used to construct components
    AbstractComponentFactory::Map ComponentFactories;
    void ConstructComponentFactories();
    void Add(const AbstractComponentFactory::Key&, AbstractComponentFactory::StrongPtr);

  };

  extern Factory* FactoryInstance;
}