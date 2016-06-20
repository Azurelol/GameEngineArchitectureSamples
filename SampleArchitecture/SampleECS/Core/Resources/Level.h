#pragma once
#include "ResourceReference.h"

namespace SPEngine {
  namespace Resources {

    class Level : public Resource {

    public:

      using Ptr = Level*;
      using StrongPtr = std::shared_ptr<Level>;

      Level(const std::string& name, const std::string& file);
      // Virtual methods which must be implemented.
      bool Save();
      bool Load();

      // Static methods cannot be virtual. Even so, providing common extension and find
      // methods for your resources is very useful, since it provides an interface between
      // the engine and however you choose to manage your resources. (Resource manager, etc)
      static std::string Extension() { return ".Level"; }
      static StrongPtr Find(const std::string& name);

    };


  }
}