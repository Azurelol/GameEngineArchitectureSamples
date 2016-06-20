/******************************************************************************/
/*!
@file   GameObject.h
@author Christian Sagel
@par    email: c.sagel\@digipen.edu
@date   4/24/2016
@brief  The Game Object composition class. 
*/
/******************************************************************************/
#pragma once
#include "..\Entity.h"

namespace SZEngine {

  //---------------------------------------------------------------------------/
  // Forward declarations
  class Space;
  class GameSession;
  //---------------------------------------------------------------------------/
  // Aliases
  class GameObject;
  using GameObjectPtr = GameObject*;
  using GameObjectContainer = std::vector<GameObjectPtr>;
  using GameObjectStrongPtr = std::unique_ptr<GameObject>;
  using GameObjectStrongContainer = std::vector<GameObjectStrongPtr>;
  //---------------------------------------------------------------------------/

  class GameObject : public Entity {
    friend class Space;

    bool Locked;
    // References
    const GameSession& GameSessionRef;
    const Space& SpaceRef;

  public:
    ZilchDeclareDerivedType(GameObject, Entity);
    GameObject(const std::string& name, const Space& space, const GameSession& gamesession);
    ~GameObject();

    // Interface    
    const Space* getSpace();
    const GameSession* getGameSession();
    void Destroy();
    void Serialize(Zilch::JsonBuilder& builder);
    void Deserialize(Zilch::JsonValue* properties);

  };


}