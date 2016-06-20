#pragma once
#include "ComponentReference.h"

namespace Components {

  FORWARD_DECLARE(Transform);

  class Camera : public Component {

  public:

    enum class ProjectionMode {
      Orthographic, // 2D
      Perspective,  // 3D
    };

  private:

    // Reference to this Camera's transform
    Transform* TransformComponent;
    // Whether this camera is currently being used or not by the
    // space it resides on
    bool Active;
    // What projection this camera is using
    ProjectionMode Projection = ProjectionMode::Perspective;
    // Camera Vectors
    Vec3 Front = Vec3(0.0f, 0.0f, -1.0f);
    Vec3 Up = Vec3(0.0f, 1.0f, 0.0f);
    Vec3 Right = Vec3(1.0f, 0.0f, 0.0f);
    // Euler Angles (Yaw and Pitch are not needed in 2D camera)
    Real Yaw = 90.0f;
    Real Pitch = 0.0f;;
    Real Roll = 90.0f;
    Real FieldOfView = 90;
    // Size of the orthographic projection. 
    Real Size = 90;
    Real NearPlane = 0.1f;
    Real FarPlane = 100.0f;

  public:
    Camera(Entity & owner);
    ~Camera();
    void Initialize();
    void Terminate();
    Mat4 getViewMatrix() const;
    Mat4 getProjectionMatrix() const;

    DEFINE_PROPERTY(bool, Active);
    DEFINE_PROPERTY(ProjectionMode, Projection);
    DEFINE_PROPERTY(Real, NearPlane);
    DEFINE_PROPERTY(Real, FarPlane);

    DEFINE_GETTER(Real, FieldOfView);
    void setFieldOfView(const Real& value);
    DEFINE_GETTER(Real, Size);
    void setSize(const Real& value);

  };

}