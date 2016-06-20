#include "Engine.h"

namespace SPEngine {

  /**************************************************************************/
  /*!
  \brief  Allows access to a system running in the engine via system type.
  \param  SystemClass The class of the system.
  \return A shared pointer to the requested system.
  */
  /**************************************************************************/
  template<typename SystemClass>
  inline SystemClass* Engine::getSystem()
  {
    for (auto& systemPtr : Systems) {
      if (std::type_index(typeid(*systemPtr.get())) == std::type_index(typeid(SystemClass)))
        return dynamic_cast<SystemClass*>(systemPtr.get());
    }
    // Throw an error if the system doesn't exist in the engine.
    throw std::range_error("The specified system does not exist.");
  }

}

