#include "Entity.h"
/*****************************************************************************/
/*!
\file   Entity.cpp
\author Christian Sagel
\par    email: c.sagel\@digipen.edu
\date   4/17/2016
\brief  The base object composition class.
*/
/******************************************************************************/

namespace SPEngine {
  
  /**************************************************************************/
  /*!
  @brief Entity constructor.
  @param name The name of the entity.
  */
  /**************************************************************************/
  Entity::Entity(std::string name) : Object(name)
  {
  }

  /**************************************************************************/
  /*!
  @brief  Entity destructor.
  */
  /**************************************************************************/
  Entity::~Entity()
  {
    RemoveAllComponents();
  }

  /**************************************************************************/
  /*!
  @brief  Adds a component onto the entity by name.
  @param  name The name of the component.
  @bool   Whether to initialize the component.
  @return A pointer to the component.
  */
  /**************************************************************************/
  Component::Ptr Entity::AddComponentByName(const std::string & name, bool initialize)
  {
    return Component::Ptr();
  }

  /**************************************************************************/
  /*!
  @brief  Returns a container of pointers to the components this entity owns.
  @return A container of component pointers.
  */
  /**************************************************************************/
  Component::Container Entity::AllComponents()
  {
    return Component::Container();
  }

  /**************************************************************************/
  /*!
  @brief  Removes all components from the entity.
  */
  /**************************************************************************/
  void Entity::RemoveAllComponents()
  {
    // C++- Factory-made components
    for (auto& component : ActiveComponents) {
      component->Terminate();
    }
    ActiveComponents.clear();

  }

}