#include "Graphical.h"

#include "../Objects/Space.h"
#include "GraphicsSpace.h"

namespace Components {

  void Graphical::Register()
  {
    getSpace()->getComponent<GraphicsSpace>()->Register(this);
  }

}