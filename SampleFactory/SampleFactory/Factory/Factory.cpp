#include "Factory.h"

namespace Systems {

  Factory* FactoryInstance = nullptr;

  /**************************************************************************/
  /*!
  @brief Factory constructor
  */
  /**************************************************************************/
  Factory::Factory() : System("Factory")
  {
    TraceObject("");
    ConstructComponentFactories();
  }

  /**************************************************************************/
  /*!
  @brief Factory initializer.
  */
  /**************************************************************************/
  void Factory::Initialize()
  {
    TraceObject("");
  }

  /**************************************************************************/
  /*!
  @brief Updates the Factory.
  @param dt The delta time.
  */
  /**************************************************************************/
  void Factory::Update(float dt)
  {
    TraceObject("");
    // Destroy all marked objects this frame
    DestroyMarkedGameObjects();
    DestroyMarkedComponents();
  }

  void Factory::Destroy(GameObject::Ptr object)
  {
    TraceObject(object->Name);
    GameObjectsToDelete.push_back(object);
  }

  void Factory::Destroy(Component::Ptr object)
  {
    TraceObject(object->Name);
    ComponentsToDelete.push_back(object);
  }

  /**************************************************************************/
  /*!
  @brief Clears the currently marked GameObjects.
  */
  /**************************************************************************/
  void Factory::DestroyMarkedGameObjects()
  {
    if (GameObjectsToDelete.empty())
      return;

    ActiveGameObjects.erase(
      std::remove_if( // Selectively remove elements in the second vector...
        ActiveGameObjects.begin(),
        ActiveGameObjects.end(),
        [&](std::unique_ptr<GameObject> const& p)
    {   // This predicate checks whether the element is contained
        // in the second vector of pointers to be removed...
      return std::find(GameObjectsToDelete.cbegin(), 
                       GameObjectsToDelete.cend(),
                       p.get()) != GameObjectsToDelete.end();}),
                       ActiveGameObjects.end());
        
    
    TraceObject("Removed '" + std::to_string(GameObjectsToDelete.size()) + "' GameObjects");
    GameObjectsToDelete.clear();

  }

  /**************************************************************************/
  /*!
  @brief Clears the currently marked Components.
  */
  /**************************************************************************/
  void Factory::DestroyMarkedComponents()
  {
    if (ComponentsToDelete.empty())
      return;

    for (auto& component : ComponentsToDelete) {
      component->Owner()->RemoveComponent(component->Name);
    }

    TraceObject("Removed '" + std::to_string(ComponentsToDelete.size()) + "' Components");
    ComponentsToDelete.clear();
  }
  /**************************************************************************/
  /*!
  @brief  Constructs a Component by a given name.
  @param  name The name of the component.
  @param  entity A reference to the entity.
  @return Returns a component by strong pointer.
  */
  /**************************************************************************/
  Component::StrongPtr Factory::ConstructComponentByName(const std::string & name, Entity & entity)
  {
    TraceObject(name);
    if (!ComponentFactories.count(name))
      throw(name + "was not found!");

    return ComponentFactories[name]->ConstructComponent(entity);
  }

  /**************************************************************************/
  /*!
  @brief  Constructs a GameObject by a given name.
  @param  name The name of the component.
  @param  space A reference to the entity.
  @return Returns a component by strong pointer.
  */
  /**************************************************************************/
  GameObject::Ptr Factory::ConstructGameObject(const std::string & name, Space & space, bool init)
  {
    TraceObject(name);
    // Construct the GameObject
    ActiveGameObjects.emplace_back(GameObject::StrongPtr(new GameObject(name, space)));
    // Add any default components here
    auto gameObject = ActiveGameObjects.back().get();
    gameObject->AddComponent("Transform", true);

    return gameObject;
  }

  Space::Ptr Factory::ConstructSpace(const std::string & name, bool init)
  {
    TraceObject(name);
    ActiveSpaces.emplace_back(Space::StrongPtr(new Space(name)));
    return ActiveSpaces.back().get();
  }

  void Factory::ConstructComponentFactories()
  {
    TraceObject("Adding all component factories...");
    // Components have to be added by hand, sadly. If we only had reflection...
    Add("Transform", std::make_unique<ComponentFactory<Components::Transform>>());
    Add("Sprite", std::make_unique<ComponentFactory<Components::Sprite>>());
  }

  void Factory::Add(const AbstractComponentFactory::Key& key, 
                    AbstractComponentFactory::StrongPtr factory)
  {
    TraceObject(key);
    // We have to use std::move to move unique_ptrs around!
    ComponentFactories.emplace(key, std::move(factory));
  }

}