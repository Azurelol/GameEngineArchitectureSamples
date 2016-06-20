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

namespace SPEngine {

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
}