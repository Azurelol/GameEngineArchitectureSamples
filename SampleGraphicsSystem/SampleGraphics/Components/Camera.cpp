#include "Camera.h"

// Cameras need a transform
#include "Transform.h"
// Camers are used by the CameraViewport component in each space
#include "../Objects/Space.h"
#include "CameraViewport.h"
// Screen
#include "../Systems/Window/Window.h"

namespace Components {

  Camera::Camera(Entity & owner) : Component("Camera", &owner)
  {
    // Don't construct a camera without a transform component!
    TransformComponent = Owner()->getComponent<Transform>();
    if (!TransformComponent) {
      TraceObject("No transform component found!");
    }
  }

  Camera::~Camera()
  {
    // If this camera is currently active, inform the camera viewport
    // that it's been destroyed
    if (Active) {
      TraceObject("Removing the default camera from the space");
      getSpace()->getComponent<CameraViewport>()->setDefaultCamera(false);
    }
  }

  void Camera::Initialize()
  {
    
  }

  void Camera::Terminate()
  {
  }
  /**************************************************************************/
  /*!
  @brief  Computes the camera view matrix based on its translation and
          Front and Up vectors.
  @return A 4x4 matrix that is used for the shader uniform "view".
  */
  /**************************************************************************/
  Mat4 Camera::getViewMatrix() const
  {
    auto& translation = TransformComponent->getTranslation();
    return glm::lookAt(translation, translation + Front, Up);
  }

  /**************************************************************************/
  /*!
  @brief  Computes the camera projection matrix based on its translation.
  @return A 4x4 matrix that is used for the shader uniform "projection".  
  */
  /**************************************************************************/
  Mat4 Camera::getProjectionMatrix() const
  {
    Mat4 projMtx;

    // Grab the current Screen Width and Height from the Window system
    auto& resolution = Systems::Window::Resolution();

    if (Projection == ProjectionMode::Orthographic) {

      auto& translation = TransformComponent->getTranslation();
      projMtx = glm::ortho(translation.x - ((float)(resolution.x) / (resolution.y)) * (100 - Size),
        translation.x + ((resolution.x) / (resolution.y)) * (100 - Size),
        translation.y - ((resolution.y) / (resolution.x)) * (100 - Size),
        translation.y + ((resolution.y) / (resolution.x)) * (100 - Size),
        NearPlane,
        FarPlane);
    }
    else if (Projection == ProjectionMode::Perspective) {


      // Calculate
      projMtx = glm::perspective(FieldOfView, 
                                 resolution.x / resolution.y, 
                                 NearPlane, 
                                 FarPlane);
    }

    return projMtx;
  }

  void Camera::setFieldOfView(const Real & value)
  {
    FieldOfView = value;
    // Clamp the FOV
    if (FieldOfView <= 1) FieldOfView = 1;
    if (FieldOfView >= 180) FieldOfView = 180;
  }

  void Camera::setSize(const Real & value)
  {
    Size = value;
    // Clamp the size
    if (Size >= 100) Size = 100;
  }

}