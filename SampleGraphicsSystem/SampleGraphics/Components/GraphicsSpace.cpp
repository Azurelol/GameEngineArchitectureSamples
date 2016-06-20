#include "GraphicsSpace.h"

// Need to access the graphics system in order to register to it!
#include "../Systems/Graphics/Graphics.h"
#include "../Objects/Entity.h"

namespace Components {

  GraphicsSpace::GraphicsSpace(Entity & owner) : Component("GraphicsSpace", &owner)
  {
    // Usually register here..
    // Systems::Graphics::getInstance()->Register(this);    
  }

  void GraphicsSpace::Initialize()
  {
    // Sometimes here, depending on how you decide to initialize all your components
    // Systems::Graphics::getInstance()->Register(this);    
  }

  void GraphicsSpace::Terminate()
  {
    // Perhaps unregister from the graphics system, yeah?
  }
  
  void GraphicsSpace::Register(Graphical * graphicalComponent)
  {
    TraceObject(graphicalComponent->Owner()->getName() + " has registered!");
    GraphicalComponents.push_back(graphicalComponent);
  }
}