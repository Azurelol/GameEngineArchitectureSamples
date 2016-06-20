#include "SpriteSource.h"

namespace Resources {

  struct SpriteSource::ImageData {
    sf::Image* Image;
    ImageData() : Image(nullptr) {}
  };

  SpriteSource::SpriteSource(const std::string & name) : Resource(name), 
                                                         Data(new ImageData())
  {
  }

  bool SpriteSource::LoadImageFromFile()
  {
    // Load the image    
    Data->Image = new sf::Image();
    Data->Image->loadFromFile(getAssetPath());
    // Textures are inverted by default
    Data->Image->flipVertically();

    if (!Data->Image->getPixelsPtr()) {
      TraceObject("Failed to load the image file!");
      return false;
    }

    TraceObject("Loaded image successfully!");
    return true;;
  }
  bool SpriteSource::GenerateTexture()
  {
    if (!Data->Image) {
      TraceObject("There's no image data loaded!");
      return false;
    }

    auto& image = Data->Image;
    
    // Generate the texture using the image data (now in memory)
    Texture.Generate(image->getSize().x, image->getSize().y, *image);
    // Unload the image data from memory now that we are done with it
    delete Data->Image;

    return true;
  }
}