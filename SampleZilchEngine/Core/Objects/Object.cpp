/*****************************************************************************/
/*!
\file   Object.cpp
\author Christian Sagel
\par    email: c.sagel\@digipen.edu
\date   4/17/2016
\brief  The base object class, from which everything else is derived.
*/
/******************************************************************************/
#include "Object.h"

// Serialization
#include "../Systems/Scripting/ZilchInterface/ZilchInterface.h"

namespace SZEngine
{
  // Statics
  unsigned Object::Created = 0;

  /*!************************************************************************\
  @brief Provides the definiton of this class to the Zilch library.
  \**************************************************************************/
  ZilchDefineType(Object, "Object", SZEngineCore, builder, type) {
    // Constructor, Destructor
    ZilchBindConstructor(builder, type, Object, "name", std::string);
    ZilchBindDestructor(builder, type, Object);
    // Methods
    SZE_BINDING_DEFINE_PROPERTY(Object, Name);
    //ZilchBindProperty(builder, type, &Object::getName, &Object::setName, "Name");
  }

  /**************************************************************************/
  /*!
  @brief  Object constructor.
  @param  name The name of the Object.
  @note   Every object in the engine derives from this Object, thus they all
  set their names through this constructor.
  */
  /**************************************************************************/
  Object::Object(std::string name) : Name(name), ObjectID(Created++)
  {
  }

  /**************************************************************************/
  /*!
  @brief  Object destructor.
  */
  /**************************************************************************/
  Object::~Object()
  {
  }

  /**************************************************************************/
  /*!
  @brief Serializes the base object.
  */
  /**************************************************************************/
  void Object::Serialize(Zilch::JsonBuilder & builder)
  {
    // Grab a reference to the state
    auto state = Systems::ZilchInterface::getState();
    SerializeByType(builder, state, ZilchTypeId(Object), this);
  }

  /**************************************************************************/
  /*!
  @brief Deserializes the base object.
  */
  /**************************************************************************/
  void Object::Deserialize(Zilch::JsonValue * properties)
  {
    // Grab a reference to the state
    auto state = Systems::ZilchInterface::getState();
    // Deserialize the GameObject properties
    DeserializeByType(properties, state, ZilchTypeId(Object), this);
  }

}