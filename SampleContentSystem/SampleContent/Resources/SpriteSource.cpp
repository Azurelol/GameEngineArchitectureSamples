#include "SpriteSource.h"

#include "ContentReference.h"

namespace Resources {

  SpriteSource::SpriteSource(const std::string & name, const std::string & file)
    : Resource(name, file)
  {
  }

  SpriteSource::StrongPtr SpriteSource::Find(const std::string & name)
  {
    // Locate this resource by accessing the content system's instance,
    // then looking it up among its resource maps
    return Systems::ContentSystem->Resources().SpriteSource.Find(name);
  }
}