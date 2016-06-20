#pragma once
#include "ResourceReference.h"

namespace Resources {
  
  class SpriteSource : public Resource {

  public:

    using Ptr = SpriteSource*;
    using StrongPtr = std::shared_ptr<SpriteSource>;

    SpriteSource(const std::string& name, const std::string& file);

    // Static methods cannot be virtual. Even so, providing common extension and find
    // methods for your resources is very useful, since it provides an interface between
    // the engine and however you choose to manage your resources. (Resource manager, etc)
    static std::string Extension() { return ".SpriteSource"; }
    static StrongPtr Find(const std::string& name);

  };

}