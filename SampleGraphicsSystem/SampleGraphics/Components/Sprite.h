/******************************************************************************/
/*!
@file   Sprite.h
@author Christian Sagel
@par    email: c.sagel\@digipen.edu
@date   5/14/2016
@brief  The Sprite component allows the graphical representation of this object
        in the world space through the drawing of sprites.
*/
/******************************************************************************/
#pragma once
#include "Graphical.h"

#include "../Resources/SpriteSource.h"

namespace Components {

  FORWARD_DECLARE(Transform);

  class Sprite : public Graphical {

    // Pimpl Idiom, ho!
    struct RenderSettings;
    // Settings used for rendering
    static RenderSettings Settings;  
    static Resources::Shader::Ptr Shader;

    // For the moment I will be making this a direct pointer
    // to the resource rather than a handle using an ID (string, unique number)
    // because we don't have a resource manager to own it
    Resources::SpriteSource* SpriteSourceHandle;
    Transform* TransformComponent;
    Vec4 Color;

  public:
    Sprite(Entity & owner);
    void Initialize();
    void Terminate();

    // Graphics System
    static void Configure();
    void Register();
    void SetUniforms(const Camera* camera); 
    void Draw();

    // Properties
    DEFINE_PROPERTY(bool, Visible);
    DEFINE_PROPERTY(Vec4, Color);
    DEFINE_PROPERTY_PTR(Resources::SpriteSource*, SpriteSourceHandle);

  };


}
