#include "EventInterface.h"

#include <iostream>

// Event system interface singleton
extern std::unique_ptr<EventInterface> Interface;

//----------------------------------------------------------------------------/
namespace Events {
  class SampleEvent : public Event {
  public:
    SampleEvent() : Event("SampleEvent") {}
    unsigned Number;
  };
}
//----------------------------------------------------------------------------/
namespace Components {
  class SampleComponent : public Component {
  public:

    void Initialize() {
      Test();
    }

    void Test() {
      // Subscribe to an event on the owner of this component     
      std::cout << "1. Connecting to the owner of this component \n";
      Interface->Connect<Events::SampleEvent>(Owner, &SampleComponent::OnSampleEvent, this);
      // Construct an event
      auto eventObj = new Events::SampleEvent();
      eventObj->Number = 5;
      std::cout << "2. Constructed the sample event with the variable Number at "
        << eventObj->Number << std::endl;
      // Dispatch it onto the owner
      std::cout << "3. Dispatched the event onto the owner \n";
      Owner->Dispatch<Events::SampleEvent>(eventObj);
      // Make sure to clean up and delete the event when you are done with it
      delete eventObj;
    }

    void OnSampleEvent(Events::SampleEvent* event) {
      // Event has been received
      std::cout << "4. Received the sample event, " << event->Number << std::endl;

    }

  };
}
//----------------------------------------------------------------------------/

int main(void) {

  // Allocate the interface object.
  Interface.reset(new EventInterface());
  // Construct an entity
  Entity* entity = new Entity();
  // Construct a component and add it to the entity
  entity->ActiveComponents.emplace_back(new Components::SampleComponent());
  auto componentPtr = entity->ActiveComponents.back().get();
  // Initialize it
  componentPtr->setOwner(entity);
  componentPtr->Initialize();
  
  return 0;
}
