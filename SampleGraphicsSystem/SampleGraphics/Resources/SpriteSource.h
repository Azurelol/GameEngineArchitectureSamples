#pragma once
#include "../Objects/Resource.h"

#include "Texture2D.h"

namespace Resources {

  class SpriteSource : public Resource {

    struct ImageData;
    std::shared_ptr<ImageData> Data;
    Texture2D Texture;

  public:
    SpriteSource(const std::string& name);
    bool LoadImageFromFile();
    bool GenerateTexture();
    DEFINE_GETTER(Texture2D, Texture);

  };
}