/*****************************************************************************/
/*!
@file   Driver.cpp
@author Christian Sagel
@par    email: c.sagel\@digipen.edu
@date   6/13/2016
@brief  Driver for the Sample Actions project.
*/
/******************************************************************************/

#include "SampleInterface.h"
#include "Entity.h"
#include "Timer.h"

//----------------------------------------------------------------------------/
class SampleComponent : public Component {
  Integer SampleInteger;
  Boolean SampleBoolean;
  Real SampleFloat;
  Vec3 SampleVec3;


public:
  SampleComponent(Entity& owner) : Component("SampleComponent", owner) {}

  void Initialize() {
    std::cout << __FUNCTION__ << std::endl;

    // 1. Create a sequence
    auto seq = Actions::Sequence(getOwner().Actions);

    // ActionDelay: Delay the sequence by the specified amount of time
    ActionDelay::Trace = false;
    Real callDelay = 1.5f;
    Actions::Delay(seq, callDelay);    

    // ActionCall: Call a provided function in the sequence
    ActionCall::Trace = false;
    Actions::Call(seq, &SampleComponent::SampleFunction, this);    

    // ActionProperty: Modify a member variable's value over a given duration    
    ActionProperty::Trace = false;
    SampleInteger = 0;
    Actions::Delay(seq, 0.5f);
    Actions::Call(seq, &SampleComponent::PrintSampleInteger, this);
    Actions::Property(seq, SampleInteger, 10, 3.0f, Ease::Linear);    
    Actions::Call(seq, &SampleComponent::PrintSampleInteger, this);
    SampleFloat = 0.0f;
    Actions::Delay(seq, 0.5f);
    Actions::Call(seq, &SampleComponent::PrintSampleReal, this);
    Actions::Property(seq, SampleFloat, 24.0f, 3.0f, Ease::Linear);
    Actions::Call(seq, &SampleComponent::PrintSampleReal, this);
    SampleVec3 = Vec3(0.0f, 0.0f, 0.0f);
    Actions::Delay(seq, 0.5f);
    Actions::Call(seq, &SampleComponent::PrintSampleVec3, this);
    Actions::Property(seq, SampleVec3, Vec3(8.0f, 16.0f, 24.0f), 3.0f, Ease::Linear);
    Actions::Call(seq, &SampleComponent::PrintSampleVec3, this);
    
    // Signal exit!
    Actions::Delay(seq, 0.25f);
    Actions::Call(seq, &SampleComponent::SignalExit, this);

  }
  
  void PrintSampleInteger() {
    std::cout << __FUNCTION__ << ": SampleInteger = '" << SampleInteger << "' \n";
  }

  void PrintSampleReal() {
    std::cout << __FUNCTION__ << ": SampleFloat = '" << SampleFloat << "' \n";
  }

  void PrintSampleVec3() {
    std::cout << __FUNCTION__ << ": SampleVec3 = '("
                              << SampleVec3.x << ","
                              << SampleVec3.y << ","
                              << SampleVec3.z << ") \n";
  }

  void SampleFunction() {
    std::cout << __FUNCTION__ << " has been called!" << std::endl;
  }

  void SignalExit() {
    std::cout << "SampleActions - END DEMONSTRATION - \n";
    std::cout << "That's all folks! You may now leave the theater~" << std::endl;
  }

};
//----------------------------------------------------------------------------/

int main(void) {
    
  std::cout << "SampleActions - BEGIN DEMONSTRATION - \n";
  Action::Trace = true;

  // 1. Instantiate the interface object (singleton)
  Interface.reset(new SampleInterface());

  // 2. Create an entity and add a component to it
  Entity* entity = new Entity();
  SampleComponent* sampleComponent = new SampleComponent(*entity);
  entity->Components.push_back(sampleComponent);
  
  // 3. Initialize the component. This will start running the tests.
  sampleComponent->Initialize();

  // 4. Start updating
  float dt = 1.0f / 60.0f;
  while (true) {
    Time::ScopeTimer frameTimer(&dt);
    Interface->Update(dt);
  }

  // Clean up
  delete entity;

  return 0;
}
