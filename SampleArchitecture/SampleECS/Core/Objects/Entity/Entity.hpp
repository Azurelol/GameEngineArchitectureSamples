#include "Entity.h"

namespace SPEngine {

  template<typename ComponentClass>
  inline ComponentClass * Entity::getComponent()
  {
    // Iterate through the container of component pointers...
    for (auto &componentPtr : ActiveComponents) {
      auto component = componentPtr.get();
      // If the component was found
      if (std::type_index(typeid(*component)) == std::type_index(typeid(ComponentClass)))
        return (reinterpret_cast<ComponentClass*>(component));
    }

    // No matching component was found
    return nullptr;
  }

}

