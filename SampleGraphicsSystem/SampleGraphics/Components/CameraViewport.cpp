#include "CameraViewport.h"

#include "../Objects/Space.h"

namespace Components {

  void CameraViewport::setDefaultCamera(Camera * cam)
  {
    // If there's a curent camera, set it to inactive first
    if (DefaultCamera)
      DefaultCamera->setActive(false);

    if (!cam)
      return;

    TraceObject("Setting the default camera to '" + cam->Owner()->getName() + "'");
    DefaultCamera = cam;
  }

  Camera * CameraViewport::getDefaultCamera()
  {
    return DefaultCamera;
  }

}

