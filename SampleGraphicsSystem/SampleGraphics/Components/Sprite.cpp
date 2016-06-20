#include "Sprite.h"

#include "GraphicsSpace.h"
#include "../Objects/Space.h""

namespace Components {

  Sprite::Sprite(Entity & owner) : Graphical("Sprite", owner), 
    Color(Vec4(1.0f, 1.0f, 1.0f, 1.0f))
  {
    // Set the transform component pointer.
    TransformComponent = Owner()->getComponent<Transform>();

    // Register();
  }

  void Sprite::Initialize()
  {
  }

  void Sprite::Terminate()
  {
  }

  void Sprite::Register()
  {
    TraceObject("Registering!");
    getSpace()->getComponent<GraphicsSpace>()->Register(this);
  }


}