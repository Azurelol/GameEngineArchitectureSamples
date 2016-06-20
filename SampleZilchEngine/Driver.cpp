/*****************************************************************************/
/*!
\file   Driver.cpp
\author Christian Sagel
\par    email: c.sagel\@digipen.edu
\date   4/17/2016
\brief  Driver for the Sample Zilch Engine project.
*/
/******************************************************************************/

// Engine
#include "Core\Systems\Scripting\Scripting.h"
#include "Core\Objects\ObjectsInclude.h"
#include "Core\Objects\Entity\EntitiesInclude.h"
#include "Core\Components\ComponentsInclude.h"

// Tests
void TestIntrospection();
void TestReflection();
void TestConstruction();
void TestSerialization();
void TestScripting();

// Local Pointers
SZEngine::SpacePtr DefaultSpace;
SZEngine::GameSession::Ptr DefaultGameSession;

// Utility
std::string PrintReal3(const Zilch::Real3& vec);
std::string BoolToString(bool b);

/**************************************************************************/
/*!
@brief  The entry point for the Engine.
@param  argc The number of arguments passed to 'main'
@param  argv An array of strings.
@return If there's an error, 1, otherwise 0.
*/
/**************************************************************************/
int main(int argc, char* argv[]) 
{  
  TraceSimple("Beginning the Zilch Integration demonstration :)\n");
  // Let's start by instantiating the Scripting system
  auto scriptingSystem = new SZEngine::Systems::Scripting();

  // Initialize the scripting system. This will initially add all the
  // known static libraries, link them and compile the executable state.
  // This object is a singleton which contains all known boundtypes.
  scriptingSystem->Initialize();

  // Create the default GameSession and Space
  DefaultGameSession = new SZEngine::GameSession("DefaultSession");
  DefaultSpace = new SZEngine::Space("DefaultSpace", *DefaultGameSession);

  //-----------------------------------------------------------------------/
  // Run the tests
  //-----------------------------------------------------------------------/
  TestIntrospection();
  TestReflection();
  TestConstruction();
  TestSerialization();
  TestScripting();

  //-----------------------------------------------------------------------/
  // Clean up
  TraceSimple("\nNow cleaning up...");
  delete scriptingSystem;
  delete DefaultGameSession;
  delete DefaultSpace;

  TraceSimple("\nEnd of Demonstration :(");
  return 0;
}

/**************************************************************************/
/*!
@brief  Demonstrates introspection by the use of a single object's BoundType. 
        This means inspecting the values of its properties.
*/
/**************************************************************************/
void TestIntrospection()
{  
  TraceNewline;
  TraceFunction("Demonstrating the inspection of a given Transform component through its boundtype!");

  // First, let's create a GameObject
  auto gameObject = new SZEngine::GameObject("Happy", *DefaultSpace, *DefaultGameSession);
  // Add a Component to it..
  auto transform = new SZEngine::Components::Transform(*gameObject);
  // Change some of its values manually
  transform->setTranslation(SZEngine::Vec3(1.0f, 2.0f, 3.0f));
  transform->setScale(SZEngine::Vec3(4.0f, 4.0f, 4.0f));
  // Now let's inspect its properties through the BoundType!
  auto transformBoundType = transform->ZilchGetDerivedType();
  TraceFunction("Now let's iterate through all its properties and print their values");
  for (auto& property : transformBoundType->AllProperties) {

    // Let's grab the current property by invoking a getter
    Zilch::ExceptionReport report;
    Zilch::Call getCall(property->Get, SZEngine::Systems::ZilchInterface::getState());
    // We associate the bound type property to that of target object
    getCall.SetHandleVirtual(Zilch::Call::This, transform);
    // We invoke the call, retrieving the property. (Because we used 'property->Get')
    // If we had wanted to set a property instead, we would have passed
    // 'property->Set' instead.
    getCall.Invoke(report);

    // Check the type of the property first!
    if (Zilch::Type::IsSame(property->PropertyType, ZilchTypeId(Zilch::Real3))) {
      // Retrieve the property from the call object
      auto real3Property = getCall.Get<Zilch::Real3>(Zilch::Call::Return);
      auto valueStr = PrintReal3(real3Property);
      // We can't print Zilch::String directly. We extract the raw string array
      // then pass it into an std string's constructor
      TraceFunction("-" + std::string(property->Name.c_str()) + " = " + valueStr);

    }
  }

  delete transform;
  delete gameObject;
}

/**************************************************************************/
/*!
@brief  Demonstrates reflection of an object through the use of its BoundType.
        This means setting the values of its properties through operations
        on the BoundType.
*/
/**************************************************************************/
void TestReflection()
{
  TraceNewline;
  TraceFunction("Demonstrating reflection of a given component through its boundtype to modify its values!");
    
  auto gameObject = new SZEngine::GameObject("Happy", *DefaultSpace, *DefaultGameSession);
  auto rigidBody = new SZEngine::Components::RigidBody(*gameObject);
  auto rigidbodyBoundType = rigidBody->ZilchGetDerivedType();
  // References to its properties
  auto& mass = rigidBody->getMass();
  auto& rotationLocked = rigidBody->getRotationLocked();
  // Let's print its initial values. Let's get lazy and not do the boundtype inspection
  // method for the sake of brevity
  TraceFunction("The initial values of some the properties of " + rigidBody->getName() + ":");
  TraceFunction("- Mass = " + std::to_string(mass));
  TraceFunction("- RotationLocked = " + BoolToString(rotationLocked));
  // Now let's modify them!
  TraceFunction("Now let's modify them through the use of BoundType and Zilch::Call's setter!");
  // Let's look up the specific properties by indexing into the property array
  // (Normally you wouldn't do this, you would iterate through the whole array
  //  since there's no "find" method at the moment)
  auto& properties = rigidbodyBoundType->AllProperties;
  auto rotationLockedProperty = properties[2];
  auto massProperty = properties[1];
  // Now let's change their values with a Zilch::Call object using 'property->Set'
  // Tip: This routine would be *really* great to have as a template method :)
  Zilch::ExceptionReport report;
  Zilch::Call setMassCall(massProperty->Set, SZEngine::Systems::ZilchInterface::getState());
  setMassCall.SetHandleVirtual(Zilch::Call::This, rigidBody);
  setMassCall.Set(0, 10.0f);
  setMassCall.Invoke(report);
  //--------------------------
  Zilch::Call setRotationLockedCall(rotationLockedProperty->Set, SZEngine::Systems::ZilchInterface::getState());
  setRotationLockedCall.SetHandleVirtual(Zilch::Call::This, rigidBody);
  setRotationLockedCall.Set(0, false);
  setRotationLockedCall.Invoke(report);
  // Now that we have modified these two properties, et's inspect their values again
  TraceFunction("The current values of the properties now are:");
  TraceFunction("- Mass = " + std::to_string(mass));
  TraceFunction("- RotationLocked = " + BoolToString(rotationLocked));

  delete gameObject;
  delete rigidBody;
}
/**************************************************************************/
/*!
@brief  Demonstrates how to use Zilch's reference-counting memory manager 
        to construct your engine's objects. In this demonstration we will
        construct a component doing so.
        Note that in order to so we have to use Zilch's Handle manager
        rather than the pointer manager we have been using so far for
        our other typess. So for this demo I have made a duplicate of the
        Transform component and set it as a Handle type.
*/
/**************************************************************************/
void TestConstruction()
{
  TraceNewline;
  TraceFunction("Demonstrating construction of a given component through Zilch!");

  auto gameObject = new SZEngine::GameObject("Tom", *DefaultSpace, *DefaultGameSession);

  TraceFunction("First, we will need access to the corresponding BoundType of the component we want to create.");
  TraceFunction("For this, we will iterate through all our BoundTypes and filter for Components");
  
  // This should be a static method! AllComponents() perhaps?
  std::vector<Zilch::BoundType*> componentBoundTypes;
  for (auto& library : SZEngine::Systems::ZilchInterface::getLibraries()) {
    auto types = library->BoundTypes.all();
    ZilchForEach(auto type, types) {
      auto baseType = type.second;
      if (Zilch::TypeBinding::IsA(baseType, ZilchTypeId(SZEngine::Component)))
        componentBoundTypes.push_back(baseType);        
    }
  }
  // Now let's print what BoundTypes of class 'Component' we have.
  // Since I know what type we want to construct, I will also a reference to that boundtype
  Zilch::BoundType* transformBoundType = nullptr;
  for (auto& type : componentBoundTypes) {
    TraceFunction("- " + std::string(type->Name.c_str()));
    if (type->Name == "TransformZilch")
      transformBoundType = type;
  }
  // Now that we have the BoundType we can create the component through the executable state.
  // It will allocate it for us and give us a Zilch::Handle object. This is an opaque pointer
  // of sorts.
  TraceFunction("Now let's construct the component '" + std::string(transformBoundType->Name.c_str()) 
                 + "' through Zilch!");
  auto state = SZEngine::Systems::ZilchInterface::getState();
  Zilch::ExceptionReport report;
  Zilch::Handle transformHandle = state->AllocateHeapObject(transformBoundType, report, 
                                                            Zilch::HeapFlags::ReferenceCounted);
  // Because we know that for C++ component derived types the only constructor that's
  // bound is the non-default one...
  Zilch::Call ctorCall(transformBoundType->Constructors[0], state);
  ctorCall.SetHandle(Zilch::Call::This, transformHandle);
  ctorCall.Set(0, gameObject);
  ctorCall.Invoke(report);

  // Now let's get an actual Component pointer out of the Zilch::Handle with some reinterpret_cast!
  TraceFunction("Let's get a pointer out of it by reinterpret_cast...");
  auto transform = reinterpret_cast<SZEngine::Components::Transform*>(transformHandle.Dereference());
  TraceFunction("And invoke the 'getName' method through the pointer. What's your name, oh component??");
  TraceFunction("(In an embarassed voice) I AM " + transform->getName() + "!!!");
  //--------------------------------------------------------------------------/
  // Note: If we were instead constructing a component that had a default ctor bound
  // we would do this instead
  if (false) {
    Zilch::Handle transformHandle = state->AllocateDefaultConstructedHeapObject(
                                            transformBoundType, report, 
                                            Zilch::HeapFlags::ReferenceCounted);
    // Now let's get an actual Component* out of the Zilch::Handle with some reinterpret_cast!
    auto transform = reinterpret_cast<SZEngine::Component::Ptr>(transformHandle.Dereference());
    
    // Note that we are constructing it through its default constructor. It is often to be
    // versatile and allow the same boilerplate done in non-default constructors to be
    // done in a "PostDefaultConstructor" that can be invoked, so the end result is the same.
    transform->PostDefaultConstructor(transformBoundType->Name.c_str(), gameObject);
  }

  //--------------------------------------------------------------------------/

  TraceFunction("Now when we exit scope, since its reference counted it will get garbage collected!");
  delete gameObject;
}

/**************************************************************************/
/*!
@brief  Demonstrates how to serialize our objects through their BoundTypes
        using Zilch's JSON library.
@note   I have gone ahead and also demonstrated the logic in the respective
        classes to demonstrate how the serialization pipeline would look.
*/
/**************************************************************************/
void TestSerialization()
{
  TraceNewline;
  TraceFunction("Demonstrating serialization of an object through Zilch!");

  // Let's create a GameObject and a component that we will serialize
  auto gameObject = new SZEngine::GameObject("Happy", *DefaultSpace, *DefaultGameSession);
  // For this demonstration I will add the component in here rather than through
  // a factory or the like
  auto transform = new SZEngine::Components::Transform(*gameObject); 
  gameObject->AddComponent(transform);
  // Let's also change some of its values
  transform->setTranslation(SZEngine::Vec3(1.0f, 2.0f, 3.0f));
  // We will need the executable state in order to start serializing
  auto state = SZEngine::Systems::ZilchInterface::getState();

  //--------------------------------------------------------------------------/
  // Serialization
  //--------------------------------------------------------------------------/
  TraceFunction("First, let's serialize the GameObject of name '" + gameObject->getName() + "'");
  // Because we will be serializing through JSON, we first create a JsonBuilder object
  // which encapsulates the whole process.
  Zilch::JsonBuilder builder;

  // You will often begin creating more scopes as you structure your serialized data
  // in a logical way. For example if you were serializing a level composed of many objects
  // the overlying level would be the outermost scope...
  builder.Begin(Zilch::JsonType::Object);
  {
    // Let's serialize the type as the key
    builder.Key("GameObject");
    builder.Begin(Zilch::JsonType::Object);
    {
      // Now let's serialize all the GameObject properties..
      gameObject->SerializeByType(builder, state, ZilchTypeId(SZEngine::GameObject), gameObject);
      // Nxt we serialize the underlying Entity properties
      gameObject->SerializeByType(builder, state, ZilchTypeId(SZEngine::Entity), gameObject);
      // Next, the base Object properties
      gameObject->SerializeByType(builder, state, ZilchTypeId(SZEngine::Object), gameObject);
      // Next, let's serialize all its components
      builder.Key("Components");
      builder.Begin(Zilch::JsonType::Object); 
      {
        for (auto& component : gameObject->AllComponents()) {
          builder.Key(component->getName().c_str());
          builder.Begin(Zilch::JsonType::Object);
          {
            // Note how for components we want to serialize its types, not the ones from its base class
            component->SerializeByType(builder, state, component->ZilchGetDerivedType(), component);

          }
          builder.End();
        }
      }
      builder.End();

    }
    builder.End();
  }
  builder.End();

  // Now let's extract the string from the builder
  std::string serializedGameObject = builder.ToString().c_str();
  TraceFunction("Now let's print the serialized data that we have constructed out of this GameObject:" + serializedGameObject);

  //--------------------------------------------------------------------------/
  // Deserialization
  //--------------------------------------------------------------------------/
  TraceFunction("Now that we have a logical structure for the serialized data, let's work from the reverse and build a new GameObject out of it!");
  // First, we will need a way to translate the string we have gotten (and maybe saved to file hoho)
  // into JSON that we can traverse for building our new GameObject
  Zilch::CompilationErrors errors;
  Zilch::JsonReader reader;
  // This will be the object encompassing from the outermost scope of the serialized data...
  Zilch::JsonValue* gameObjectData = reader.ReadIntoTreeFromString(errors, 
                                     serializedGameObject.c_str(), Zilch::String(), nullptr);
  // The serialized properties will be found one scope down inside "GameObject"
  auto gameObjectProperties = *gameObjectData->OrderedMembers.data();
  // Let's create a new GameObject which will start on a "blank slate"
  TraceFunction("Now let's create a new default GameObject...");
  auto newGameObject = new SZEngine::GameObject("Nameless", *DefaultSpace, *DefaultGameSession);
  SZEngine::Components::Transform* newTransform = nullptr;
  TraceFunction("What's your name (before I have performed the deserialization magic routine on you)?");
  TraceFunction("My name is... '" + newGameObject->getName() + "'");
  // Now let's deserialize it using the data above..
  // First, let's deserialize all its properties..
  newGameObject->DeserializeByType(gameObjectProperties->Value, state, ZilchTypeId(SZEngine::GameObject), newGameObject);
  newGameObject->DeserializeByType(gameObjectProperties->Value, state, ZilchTypeId(SZEngine::Entity), newGameObject);
  newGameObject->DeserializeByType(gameObjectProperties->Value, state, ZilchTypeId(SZEngine::Object), newGameObject);
  // Next, let's build the components that were recorded in the serialization step
  // This is why its useful to structure the serialized data logically!
  auto componentsData = gameObjectProperties->Value->GetMember("Components")->OrderedMembers.all();
  for (auto& componentData : componentsData) {
    // Let's get the name of the component..
    auto componentName = std::string(componentData->Key.c_str());
    // We will use that name as a key/index into a component factory.. or
    // through our known Component BoundTypes! (Remember, they all have Name so we can
    // just match with that) ...
    SZEngine::Component::Ptr component = nullptr;    
    // Construct the component
    // But... because this example is not about either of those I will just be expedient
    // and hack it. Please do use a factory model, though :)
    if (componentName == "Transform") {
      component = new SZEngine::Components::Transform(*newGameObject);
      newGameObject->AddComponent(component);
      // Because I haven't provided a way to retrieve a component pointer from a GameObject easily
      // yet, let's get lazy
      newTransform = dynamic_cast<SZEngine::Components::Transform*>(component);
    }
    // If it was constructed...
    if (component) {
      auto componentProperties = componentData->Value;
      component->Deserialize(componentProperties);
    }
  }
  TraceFunction("Now that we have deserialized into it, let's ask him again. What is your name?");
  TraceFunction("My name is now '" + newGameObject->getName() + "'");
  auto translation = newTransform->getTranslation();
  TraceFunction("My translation is at: (" + std::to_string(translation.x) + "," 
                                          + std::to_string(translation.y) + "," 
                                          + std::to_string(translation.z) + ")");

  // We don't have to delete the components anymore since they are now owned
  // unique_ptrs from the GameObjects
  delete gameObject;
  //delete transform;
  delete newGameObject;
  //delete newTransform;
}

/**************************************************************************/
/*!
@brief  Demonstrates how to create components through Zilch scripts from
        valid Zilch code and how to interact with them. 
*/
/**************************************************************************/
void TestScripting()
{
  TraceNewline;
  TraceFunction("Demonstrating serialization of an object through Zilch!");

  // Let's create a GameObject and a component that we will serialize
  auto gameObject = new SZEngine::GameObject("Happy", *DefaultSpace, *DefaultGameSession);

  TraceFunction("Because we have the ZilchComponent class, we can construct a component written from Zilch scripts.");
  TraceFunction("Before we do so, let's look at what BoundTypes of base class 'Component' we have available:");
  // I have written a function that will iterate through all known libraries for BoundTypes of base class 'Component'
  for (auto& component : SZEngine::Component::All()) {
    TraceFunction("- " + std::string(component->Name.c_str()) + "'");
  }
  TraceNewline;

  // Load the script from file
  std::string scriptName = "Player";
  std::string scriptCode;
  std::ifstream scriptFile(scriptName + ".Zilch");
  if (scriptFile) {
    scriptCode = std::string((std::istreambuf_iterator<char>(scriptFile)),
                            (std::istreambuf_iterator<char>()));
  }
  else {
    TraceFunction("The file is gone???");
    exit(-1);
  }
  TraceFunction("First, let's load the script '" + scriptName + "' from file. Let's read it:\n" + scriptCode);

  // Now let's add it to the executable state through a library
  TraceFunction("Now let's add it to the executable state. We will create a new Zilch::Project...");
  Zilch::Project scriptProject;
  Zilch::EventConnect(&scriptProject, Zilch::Events::CompilationError, Zilch::DefaultErrorCallback);
  TraceFunction("Next, we will add the code of the script to it, then compile it.");
  scriptProject.AddCodeFromString(scriptCode.c_str(), scriptName.c_str(), "Player");
  auto& dependencies = SZEngine::Systems::ZilchInterface::getLibraries();
  auto state = SZEngine::Systems::ZilchInterface::getState();
  auto scriptLib = scriptProject.Compile("ZilchComponents", dependencies, Zilch::EvaluationMode::Project);
  TraceFunction("After that we will rebuild the executable state with it so it gets registered as a BoundType");
  // Note: Thiss whole procedure should be done internally inside whatever class is managing the Zilch binding. 
  //       Do not expose your dependencies outside if you cannot help it. If they get wiped out in the middle of 
  //       runtime unexpectedly, very bad things will happen. 
  //       (I am only doing this here to demonstrate)
  dependencies.clear();
  dependencies.push_back(Zilch::Core::GetInstance().GetLibrary());
  dependencies.push_back(SZEngine::SZEngineCore::GetInstance().GetLibrary());
  dependencies.push_back(scriptLib);
  state = dependencies.Link();
  
  //--------------------------------------------------------------------------/
  TraceFunction("Now that we have compiled it, let's check what BoundTypes we now have access to:");
  // I have written a function that will iterate through all known libraries for BoundTypes of base class 'Component'
  auto componentTypes = SZEngine::Component::All(); 
  Zilch::BoundType* playerBoundType = nullptr;
  for (auto& component : componentTypes) {
    TraceFunction("- " + std::string(component->Name.c_str()) + "");
    if (component->Name == "Player")
      playerBoundType = component;
  }
  TraceNewline;

  // Now let's construct the component with the newly registered BoundType
  TraceFunction("Now that we have registered a new BoundType, let's construct a new component with it!");
  Zilch::ExceptionReport report;
  auto playerHandle = state->AllocateDefaultConstructedHeapObject(playerBoundType, report, 
                                                                  Zilch::HeapFlags::ReferenceCounted);
  // Let's grab the pointer from the handle
  auto player = SZEngine::Component::Dereference(playerHandle);
  // Save its handle (Perhaps there's a better way of doing this backward kind of thing
  player->setHandle(playerHandle);
  // Call the post-constructor step
  player->PostDefaultConstructor(playerBoundType->Name.c_str(), gameObject);
  TraceFunction("Let's add it to the GameObject...");
  // Perhaps add it to the GameObject
  gameObject->AddComponent(playerHandle);
  // Let's find the Zilch functions
  auto initializeFunc = playerBoundType->FindFunction("Initialize", Zilch::Array<Zilch::Type*>(),
    ZilchTypeId(void), Zilch::FindMemberOptions::DoNotIncludeBaseClasses);
  auto teerminateFunc = playerBoundType->FindFunction("Terminate", Zilch::Array<Zilch::Type*>(),
    ZilchTypeId(void), Zilch::FindMemberOptions::DoNotIncludeBaseClasses);
  // Now let's call them
  TraceFunction("Now let's call its initialize method. It will be executing the Zilch code!");  
  Zilch::Call init(initializeFunc, state);
  init.Set<Zilch::Handle>(Zilch::Call::This, playerHandle);
  init.Invoke(report);
  //player->Initialize();
  TraceFunction("Now let's call its terminate method!");
  Zilch::Call terminate(teerminateFunc, state);
  terminate.Set<Zilch::Handle>(Zilch::Call::This, playerHandle);
  terminate.Invoke(report);
  //player->Terminate();
  TraceFunction("Now let's try looking at its properties like how we did before!");
  auto& playerProperties = playerBoundType->AllProperties;
  for (auto& property : playerProperties) {
    Zilch::Call getCall(property->Get, state);
    getCall.SetHandle(Zilch::Call::This, playerHandle);
    getCall.Invoke(report);
    // Check the type of the property first!
    if (Zilch::Type::IsSame(property->PropertyType, ZilchTypeId(Zilch::Integer))) {
      auto integer = getCall.Get<Zilch::Integer>(Zilch::Call::Return);
      TraceFunction("- " + std::string(property->Name.c_str()) + " = " + std::to_string(integer));
    }
  }
  TraceFunction("Now that we have proved we were able to modify the values through reflection, we have come full circle!");

  delete gameObject;
}

///////////////////////////
// Utility functions here
///////////////////////////
std::string PrintReal3(const Zilch::Real3 & vec)
{
  return std::string("(" + std::to_string(vec.x) + "," +
                           std::to_string(vec.y) + "," +
                           std::to_string(vec.z) + ")");
}

std::string BoolToString(bool b)
{
  return b ? "true" : "false";
}