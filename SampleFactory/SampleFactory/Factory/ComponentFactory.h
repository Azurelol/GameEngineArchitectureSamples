#pragma once
#include "../Engine/Components/ComponentsInclude.h"

#include <unordered_map>

namespace Systems {

  /**************************************************************************/
  /*!
  @class  The AbstractComponentFactory class is the one we have containers of.
  */
  /**************************************************************************/
  class AbstractComponentFactory {
  public:
    using Key = std::string;
    virtual Component::StrongPtr ConstructComponent(Entity& owner) = 0;
    using StrongPtr = std::unique_ptr<AbstractComponentFactory>;
    using Map = std::unordered_map<Key, StrongPtr>;
  };

  /**************************************************************************/
  /*!
  @class  Every derived 'Component' has its own instantiated factory that is
  used to make instances of that component type.
  */
  /**************************************************************************/
  template <typename ComponentClass>
  class ComponentFactory : public AbstractComponentFactory {
  public:
    Component::StrongPtr ConstructComponent(Entity& owner) {
      return std::make_unique<ComponentClass>(owner);
    }
  };

}