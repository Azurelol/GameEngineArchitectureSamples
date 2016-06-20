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
#include "Space.h"

// GameSession
#include "..\GameSession\GameSession.h"

namespace SPEngine {

  /**************************************************************************/
  /*!
  @brief Space constructor.
  @param name The name of the space.
  @param gameSession A reference to the GameSession this Space belongs to.
  */
  /**************************************************************************/
  Space::Space(const std::string & name, const GameSession & gameSession) 
    : Entity(name), GameSessionRef(gameSession)
  {
  }

  /**************************************************************************/
  /*!
  @brief Space destructor.
  */
  /**************************************************************************/
  Space::~Space()
  {
    SPTraceF;
  }

  /**************************************************************************/
  /*!
  @brief  Initializes the space.
  */
  /**************************************************************************/
  void Space::Initialize()
  {
    SPTraceF;
  }

  /**************************************************************************/
  /*!
  @brief  Loads the specified level.
  @param  A reference to the level resource.
  */
  /**************************************************************************/
  void Space::LoadLevel(const Resources::Level::Ptr & level)
  {
    SPTraceN("Loading the level '" + level->getName() + "'");
  }

  /**************************************************************************/
  /*!
  @brief  Loads the specified level.
  @param  The name of the level. (It will be looked up in the content system)
  */
  /**************************************************************************/
  void Space::LoadLevel(const std::string & name)
  {
    SPTraceN("Loading the level '" + name + "'");
  }

  /**************************************************************************/
  /*!
  @brief  Reloads the current level.
  */
  /**************************************************************************/
  void Space::ReloadLevel()
  {
    SPTraceF;
  }

  /**************************************************************************/
  /*!
  @brief  Destroys the space.
  */
  /**************************************************************************/
  void Space::Destroy()
  {
    SPTraceF;
  }

  /**************************************************************************/
  /*!
  @brief  Returns a reference to the GameSession.
  @return A pointer to the GameSession.
  */
  /**************************************************************************/
  const GameSession * Space::getGameSession()
  {
    return &GameSessionRef;
  }
}