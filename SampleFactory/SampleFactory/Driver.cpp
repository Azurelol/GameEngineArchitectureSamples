#include "Factory\Factory.h"

int main(void) {
  
  TraceF("Factory Demonstration Start!\n");
  // Instantiate the factory
  Systems::FactoryInstance = new Systems::Factory();
  // Create a space with it. The second argument is for whether to initialize it.
  Space::Ptr space = Systems::FactoryInstance->ConstructSpace("SampleSpace", true);
  // Request the space to create a GameObject. It will return a pointer for you.
  GameObject::Ptr gameObject = space->CreateGameObject("SampleGameObject");
  // Add a component to it
  Components::Sprite* sprite = 
    dynamic_cast<Components::Sprite*>(gameObject->AddComponent("Sprite"));
  // Intialize the component
  sprite->Initialize();

  //--------------------------------------------------------------------------/
  // Now destroy the component. This will get destroyed the next time the Factory
  // system gets updated (So destruction happens on the next frame always).
  // This will save you a lot of headaches.
  sprite->Destroy();
  // Let's print how many components this GameObject has 
  TraceF(gameObject->Name + " has '" + std::to_string(gameObject->AllComponents().size())
        + "' components");
  // Now let's update the Factory so that the component gets deleted
  Systems::FactoryInstance->Update(42);
  // Let's print how many components it has again
  TraceF(gameObject->Name + " now has '" + std::to_string(gameObject->AllComponents().size())
         + "' components");
  // 
  //--------------------------------------------------------------------------/
  // Let's print how many gameobjects the space has
  TraceF(space->Name + " has '" + std::to_string(space->AllGameObjects().size())
    + "' gameObjects");
  // Let's now destroy the game object
  gameObject->Destroy();
  // Update the factory to advance to the next frame
  Systems::FactoryInstance->Update(24);
  // Let's print how many gameobjects the space has
  TraceF(space->Name + " now has '" + std::to_string(space->AllGameObjects().size())
    + "' gameObjects");

  std::cout << std::endl;
  TraceF("Factory Demonstration End!");
  delete Systems::FactoryInstance;
  return 0; 

}