/******************************************************************************/
/*!
\file   GameSession.cpp
\author Christian Sagel
\par    email: c.sagel\@digipen.edu
\date   4/24/2016
\brief  The container object for the spaces in the game, at the highest hierarchy.
*/
/******************************************************************************/
#include "GameSession.h"

namespace SZEngine {

  /*!************************************************************************\
  @brief  GameSession Definition
  \**************************************************************************/
  ZilchDefineType(GameSession, "GameSession", SZEngineCore, builder, type) {
    SZE_BINDING_SET_HANDLE_TYPE_POINTER;
    // Constructor / Destructor
    ZilchBindConstructor(builder, type, GameSession, "name", std::string);
    ZilchBindDestructor(builder, type, GameSession);
    ZilchBindMethod(builder, type, &GameSession::CreateNamedSpace, ZilchNoOverload, "CreateNamedSpace", "name");
    ZilchBindMethod(builder, type, &GameSession::Quit, ZilchNoOverload, "Quit", ZilchNoNames);
  }

  /**************************************************************************/
  /*!
  @brief GameSession constructor.
  @param name The name to use for this GameSession.
  */
  /**************************************************************************/
  GameSession::GameSession(const std::string & name) : Entity(name)
  {
    TraceObject("Created '" + name + "'");
  }

  /**************************************************************************/
  /*!
  @brief GameSession destructor.
  */
  /**************************************************************************/
  GameSession::~GameSession()
  {
    TraceObject("");
  }

  /**************************************************************************/
  /*!
  @brief GameSession Initializer.
  */
  /**************************************************************************/
  void GameSession::Initialize()
  {
    TraceObject("");
    // Initialize all spaces
    for (auto& space : ActiveSpaces) {
      space.second->Initialize();
    }
  }
  
  /**************************************************************************/
  /*!
  @brief GameSession Initializer.
  */
  /**************************************************************************/
  void GameSession::Quit()
  {
    // Ask the engine to quit here..
  }

  /**************************************************************************/
  /*!
  @brief  Creates a space with the given name.
  @param  The name of the space.
  @return A pointer to the space.
  */
  /**************************************************************************/
  SpacePtr GameSession::CreateNamedSpace(const std::string & name)
  {
    auto space = ActiveSpaces.find(name);
    if (space != ActiveSpaces.end())
      return (*space).second.get();

    // If the space doesn't exist, create it
    else
      ActiveSpaces.emplace(name, SpaceStrongPtr(new Space(name, *this)));
    TraceObject("Added the Space '" + name + "'");
  }
  
  /**************************************************************************/
  /*!
  @brief  Returns all spaces.
  @return A container of pointers to the all active spaces.
  */
  /**************************************************************************/
  SpaceContainer & GameSession::AllSpaces()
  {
    return ActiveSpaces;
  }
}