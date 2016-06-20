#pragma once
#include "ComponentReference.h"

// The GraphicsSpace deals in providing an interface as well as
// a container for graphical components
#include "Graphical.h"
#include "Sprite.h"
// The CameraViewport component...
#include "CameraViewport.h"

namespace Components {

  class GraphicsSpace : public Component {

    CameraViewport* Viewport;
    Graphical::Container GraphicalComponents;

  public:

    GraphicsSpace(Entity & owner);
    void Initialize();
    void Terminate();
    void Register(Graphical* graphicalComponent);
    DEFINE_GETTER(Graphical::Container, GraphicalComponents);
    DEFINE_PROPERTY_PTR(CameraViewport*, Viewport);

  };

}
