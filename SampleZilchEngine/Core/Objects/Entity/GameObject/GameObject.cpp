/******************************************************************************/
/*!
@file   GameObject.h
@author Christian Sagel
@par    email: c.sagel\@digipen.edu
@date   4/24/2016
@brief  The Game Object composition class.
*/
/******************************************************************************/
#include "GameObject.h"

#include "../EntitiesInclude.h"
// Serialization
#include "../../../Systems/Scripting/ZilchInterface/ZilchInterface.h"

namespace SZEngine {

  /*!************************************************************************\
  @brief  GameObject Definition
  \**************************************************************************/
  ZilchDefineType(GameObject, "GameObject", SZEngineCore, builder, type) {
    SZE_BINDING_SET_HANDLE_TYPE_POINTER;
    // Constructor / Destructor
    ZilchBindConstructor(builder, type, GameObject, "name, space, gamesession", std::string, Space&, GameSession&);
    ZilchBindDestructor(builder, type, GameObject);    
    // Methods
    ZilchBindMethod(builder, type, &GameObject::Destroy, ZilchNoOverload, "Destroy", ZilchNoNames);
  }

  /**************************************************************************/
  /*!
  @brief  GameObject constructor.
  @param  The name of the GameObject.
  @param  A reference to the Space.
  @param  A reference to the GameSession.
  */
  /**************************************************************************/
  GameObject::GameObject(const std::string & name, const Space & space, const GameSession & gamesession) 
    : Entity(name), SpaceRef(space), GameSessionRef(gamesession) 
  {
  }

  /**************************************************************************/
  /*!
  @brief  GameObject destructor.
  */
  /**************************************************************************/
  GameObject::~GameObject()
  {
  }

  /**************************************************************************/
  /*!
  @brief  Grabs a pointer to the Space this GameObject resides on.
  */
  /**************************************************************************/
  const Space * GameObject::getSpace()
  {
    return &SpaceRef;
  }

  /**************************************************************************/
  /*!
  @brief  Grabs a pointer to the GameSession this GameObject resides on.
  */
  /**************************************************************************/
  const GameSession * GameObject::getGameSession()
  {
    return &GameSessionRef;
  }

  /**************************************************************************/
  /*!
  @brief  Marks the GameObject to be destroyed by the factory system on the
          next frame.
  */
  /**************************************************************************/
  void GameObject::Destroy()
  {
  }

  /**************************************************************************/
  /*!
  @brief Serializes a GameObject.
  @param builder A reference to the JSON builder.
  @note  This will serialize the entity's properties, then its components.
  */
  /**************************************************************************/
  void GameObject::Serialize(Zilch::JsonBuilder & builder)
  {
    // Grab a reference to the state
    auto state = Systems::ZilchInterface::getState();

    // First, we will create the key before starting the outermost scope
    // of the JSON object representing this GameObject's serialized data
    // (We use keys later for deserialization, to know where to look)
    builder.Key("GameObject");
    builder.Begin(Zilch::JsonType::Object);
    {
      // Serialize GameObject properties
      SerializeByType(builder, state, ZilchTypeId(GameObject), this);
      // Serialize the underlying Entity object (including components)
      Entity::Serialize(builder);
      // Serialize all children and their children (This happens recursively)
      // Add children code here :D
    }
    builder.End();
  }

  /**************************************************************************/
  /*!
  @brief Deseserializes a GameObject
  @param properties A pointer to the object containing the properties.
  @note  This will deserialize the entity's properties, then its components.
  */
  /**************************************************************************/
  void GameObject::Deserialize(Zilch::JsonValue * properties)
  {
    // Grab a reference to the state
    auto state = Systems::ZilchInterface::getState();
    // Deserialize the underlying Entity
    Entity::Deserialize(properties);
    // Deserialize the GameObject properties
    DeserializeByType(properties, state, ZilchTypeId(GameObject), this);
  }
}