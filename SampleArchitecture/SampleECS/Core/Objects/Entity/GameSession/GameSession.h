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

namespace SPEngine {

  // Forward declaration to provide engine access to private members
  class Engine;

  class GameSession : public Entity {
    friend class Engine;

    SpaceContainer ActiveSpaces;
    SpacePtr DefaultSpace;

  public:
    GameSession(const std::string& name);
    ~GameSession();
    // Interface
    void Initialize();
    void Quit();
    // Spaces    
    SpacePtr CreateNamedSpace(const std::string& name);
    SpaceContainer& AllSpaces();
    // Aliases
    using StrongPtr = std::unique_ptr<GameSession>;

  };

}