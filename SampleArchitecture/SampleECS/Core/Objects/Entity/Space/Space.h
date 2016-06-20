/******************************************************************************/
/*!
@file   Space.h
@author Christian Sagel
@par    email: c.sagel\@digipen.edu
@date   4/24/2016
@brief  Spaces are containers for game objects. When a level is loaded into
        a space, all the game objects from that level are put into the space.
        Each space has its own instances of interfaces to systems to the engine.
*/
/******************************************************************************/
#pragma once
#include "..\Entity.h"

// GameObjects
#include "..\GameObject\GameObject.h"
#include "..\..\..\Resources\Level.h"

namespace SPEngine {

  //---------------------------------------------------------------------------/
  // Forward declarations
  class GameSession;
  //---------------------------------------------------------------------------/
  //---------------------------------------------------------------------------/
  // Aliases
  class Space;
  using SpacePtr = Space*;
  using SpaceStrongPtr = std::shared_ptr<Space>;
  using SpaceContainer = std::unordered_map<std::string, SpaceStrongPtr>;
  //---------------------------------------------------------------------------/

  class Space : public Entity {
    friend class GameSession;

    // References
    const GameSession& GameSessionRef;   

    void Initialize();

  public:
    Space(const std::string& name, const GameSession& gameSession);
    ~Space();

    //---------------------------------------------------------------------------/
    // Interface
    //---------------------------------------------------------------------------/
    // We provide two methods for loading levels. We use the string one mostly
    // in the context of a scripting language.
    void LoadLevel(const Resources::Level::Ptr& level);
    void LoadLevel(const std::string& levelName);
    void ReloadLevel();
    void Destroy();
    const GameSession* getGameSession();
    //---------------------------------------------------------------------------/

  };

}