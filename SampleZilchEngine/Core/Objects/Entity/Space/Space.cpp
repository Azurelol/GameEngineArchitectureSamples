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

// Levels
#include "..\..\..\Resources\Serialization\Level.h"
// GameSession
#include "..\GameSession\GameSession.h"

namespace SZEngine {

  /*!************************************************************************\
  @brief  Space Definition
  \**************************************************************************/
  ZilchDefineType(Space, "Space", SZEngineCore, builder, type) {
    SZE_BINDING_SET_HANDLE_TYPE_POINTER;
    // Constructor / Destructor
    ZilchBindConstructor(builder, type, Space, "name, gamesession", std::string, GameSession&);
    ZilchBindDestructor(builder, type, Space);
    // Methods
    ZilchBindMethod(builder, type, &Space::Destroy, ZilchNoOverload, "Destroy", ZilchNoNames);
    ZilchBindMethod(builder, type, &Space::LoadLevel, (void (Space::*)(const std::string&)), "LoadLevel", "level");
    ZilchBindMethod(builder, type, &Space::ReloadLevel, ZilchNoOverload, "ReloadLevel", ZilchNoNames);
  }

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
    TraceObject("Name = '" + name + "', GameSession = '" + gameSession.getName() + "'");
  }

  /**************************************************************************/
  /*!
  @brief Space destructor.
  */
  /**************************************************************************/
  Space::~Space()
  {
    TraceObject("");
  }

  /**************************************************************************/
  /*!
  @brief  Initializes the space.
  */
  /**************************************************************************/
  void Space::Initialize()
  {
    TraceObject("");;
  }

  /**************************************************************************/
  /*!
  @brief  Loads the specified level.
  */
  /**************************************************************************/
  void Space::LoadLevel(const std::string & name)
  {
    TraceObject("Loading the level '" + name + "'");
    // Find a reference to the level resource
    auto levelRef = Level::Find(name);
    // Load it
  }

  /**************************************************************************/
  /*!
  @brief  Reloads the current level.
  */
  /**************************************************************************/
  void Space::ReloadLevel()
  {
    TraceObject("");;
  }

  /**************************************************************************/
  /*!
  @brief  Destroys the space.
  */
  /**************************************************************************/
  void Space::Destroy()
  {
    TraceObject("");;
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