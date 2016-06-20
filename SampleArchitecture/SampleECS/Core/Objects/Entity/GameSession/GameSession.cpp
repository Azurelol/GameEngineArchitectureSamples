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

namespace SPEngine {

  /**************************************************************************/
  /*!
  @brief GameSession constructor.
  @param name The name to use for this GameSession.
  */
  /**************************************************************************/
  GameSession::GameSession(const std::string & name) : Entity(name)
  {
    SPTraceN("has been created!");
  }

  /**************************************************************************/
  /*!
  @brief GameSession destructor.
  */
  /**************************************************************************/
  GameSession::~GameSession()
  {
  }

  /**************************************************************************/
  /*!
  @brief GameSession Initializer.
  */
  /**************************************************************************/
  void GameSession::Initialize()
  {
    SPTraceF;
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
    SPTraceF;
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

    SPTraceN("added the Space '" + name + "'");    
    return (*ActiveSpaces.find(name)).second.get();
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