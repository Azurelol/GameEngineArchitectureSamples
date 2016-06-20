#include "ZilchComponent.h"

// Serialization, State
#include "../../Systems/Scripting/ZilchInterface/ZilchInterface.h" 
// Binding
#include "..\Entity\EntitiesInclude.h"
namespace SZEngine {

  /*!************************************************************************\
  @brief  Zilch Component Definition
  \**************************************************************************/
  ZilchDefineType(ZilchComponent, "ZilchComponent", SZEngineCore, builder, type) {
    // Constructor / Destructor    
    ZilchBindConstructor(builder, type, ZilchComponent, ZilchNoNames);
    ZilchBindDestructor(builder, type, ZilchComponent);
    // Methods
    ZilchBindMethod(builder, type, &ZilchComponent::Initialize, ZilchNoOverload, "Initialize", ZilchNoNames)->IsVirtual = true;
    ZilchBindMethod(builder, type, &ZilchComponent::Terminate, ZilchNoOverload, "Terminate", ZilchNoNames)->IsVirtual = true;
    ZilchBindProperty(builder, type, &ZilchComponent::Owner, ZilchNoSetter, "Owner");
    ZilchBindProperty(builder, type, &ZilchComponent::getSpace, ZilchNoSetter, "Space");
    ZilchBindProperty(builder, type, &ZilchComponent::getGameSession, ZilchNoSetter, "GameSession");
  }

  /**************************************************************************/
  /*!
  @brief ZilchComponent default constructor. This is the only one we will be using
         since we will allocate using default constructor then call the 
         PostDefaultConstructor method after.
  */
  /**************************************************************************/
  ZilchComponent::ZilchComponent()
  {
    // Finds all functions
    FindFunctions();
  }
  /**************************************************************************/
  /*!
  @brief ZilchComponent destructor.
  */
  /**************************************************************************/
  ZilchComponent::~ZilchComponent()
  {
  }

  /**************************************************************************/
  /*!
  @brief Initializes the ZilchComponent.
  */
  /**************************************************************************/
  void ZilchComponent::Initialize()
  {

    if (!InitializeFunc)
      return;

    // Invoke the Initialize method
    Zilch::Call init(this->InitializeFunc, Systems::ZilchInterface::getState());
    init.Set<Zilch::Handle>(Zilch::Call::This, getHandle());
    init.Invoke(Report);
    auto messages = Report.GetConcatenatedMessages();
    //ErrorIf("Something happened");
    TraceFunction("Initialize ho!");
  }

  /**************************************************************************/
  /*!
  @brief Terminates the ZilchComponent.
  */
  /**************************************************************************/
  void ZilchComponent::Terminate()
  {
    if (!TerminateFunc)
      return;

    // Invoke the Initialize method
    Zilch::Call terminate(this->TerminateFunc, Systems::ZilchInterface::getState());
    terminate.Set<Zilch::Handle>(Zilch::Call::This, getHandle());
    terminate.Invoke(Report);
  }

  /**************************************************************************/
  /*!
  @brief Serializes a ZilchComponent.
  @param builder A reference to the JSON builder.
  @note  This will serialize the component and all its properties.
  */
  /**************************************************************************/
  void ZilchComponent::Serialize(Zilch::JsonBuilder & builder)
  {
    // Grab a reference to the state
    auto state = Systems::ZilchInterface::getState();

    builder.Key(this->getName().c_str());
    builder.Begin(Zilch::JsonType::Object);
    SerializeByType(builder, state, this->ZilchGetDerivedType(), this, this->getHandle());
    builder.End();
  }

  /**************************************************************************/
  /*!
  @brief Deserializes a ZilchComponent.
  @param builder A pointer to the object containing the properties.
  @note  This will deserialize the Component's properties.
  */
  /**************************************************************************/
  void ZilchComponent::Deserialize(Zilch::JsonValue * properties)
  {
    // Grab a reference to the state
    auto state = Systems::ZilchInterface::getState();
    DeserializeByType(properties, state, this->ZilchGetDerivedType(), this, this->getHandle());
  }

  /**************************************************************************/
  /*!
  @brief Finds all common functions to be passed to Zilch.
  */
  /**************************************************************************/
  void ZilchComponent::FindFunctions()
  {
    auto boundType = this->ZilchGetDerivedType();
    InitializeFunc = boundType->FindFunction("Initialize", Zilch::Array<Zilch::Type*>(), 
                                             ZilchTypeId(void), Zilch::FindMemberOptions::DoNotIncludeBaseClasses);
    TerminateFunc = boundType->FindFunction("Terminate", Zilch::Array<Zilch::Type*>(),
                                            ZilchTypeId(void), Zilch::FindMemberOptions::DoNotIncludeBaseClasses);

  }

  bool ZilchComponent::IsA(Component::Ptr component)
  {
    return false;
  }
}