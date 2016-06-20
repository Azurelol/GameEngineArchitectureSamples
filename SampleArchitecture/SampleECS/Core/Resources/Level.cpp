#include "Level.h"

namespace SPEngine {
  namespace Resources {


    Level::Level(const std::string & name, const std::string & file) : Resource(name, file)
    {
    }

    bool Level::Save()
    {
      return false;
    }

    bool Level::Load()
    {
      return false;
    }

    Level::StrongPtr Level::Find(const std::string & name)
    {
      return StrongPtr();
    }

  }
}