/******************************************************************************/
/*!
\file   GameSession.h
\author Christian Sagel
\par    email: c.sagel\@digipen.edu
\date   4/24/2016
\brief  The container object for the spaces in the game, at the highest hierarchy.
*/
/******************************************************************************/
#pragma once
#include "..\Entity.h"

// Spaces
#include "..\Space\Space.h"

namespace SZEngine {

  class GameSession : public Entity {
    SpaceContainer ActiveSpaces;
    SpacePtr DefaultSpace;

  public:
    ZilchDeclareDerivedType(GameSession, Entity);
    GameSession(const std::string& name);
    ~GameSession();
    // Interface
    void Initialize();
    void Quit();
    // Spaces    
    SpacePtr CreateNamedSpace(const std::string& name);
    SpaceContainer& AllSpaces();
    SZE_DEFINE_PROPERTY(SpacePtr, DefaultSpace);
    // Aliases
    using Ptr = GameSession*;
    using StrongPtr = std::unique_ptr<GameSession>;

  };

}