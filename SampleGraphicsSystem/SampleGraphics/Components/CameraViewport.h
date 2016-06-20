#pragma once
#include "Camera.h"

namespace Components
{
  class CameraViewport : public Component {

    Camera* DefaultCamera;

  public:

    CameraViewport(Entity& owner) : Component("CameraViewport", &owner), 
      DefaultCamera(nullptr) {}
    void Initialize() {}
    void Terminate() {}
    void setDefaultCamera(Camera* cam);
    Camera* getDefaultCamera();
    //DEFINE_PROPERTY_PTR(Camera*, DefaultCamera);

  };
}
