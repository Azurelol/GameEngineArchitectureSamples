#pragma once
#include "../Resources/ResourcesInclude.h"

namespace Systems {

  template <typename ResourceType>
  class ResourceMap {
  public:
    using Ptr = std::shared_ptr<ResourceType>;
    using Map = std::unordered_map<Resource::Handle, Ptr>;

    void Add(Ptr resource) {
      Container.insert(std::pair<Resource::Handle, Ptr>(resource->getName(), resource));
    }
    bool Remove(const Resource::Handle& handle) {
      if (!Container.count(handle))
        return false;
      
      // Note. Does not call delete on the pointers.
      Container.erase(handle);
      return true;
    }

    bool Has(const Resource::Handle&) {
      if (!Container.count(handle))
        return false;
      return true;
    }

    Ptr Find(const Resource::Handle& handle) {
      if (!Container.count(handle))
        return nullptr;
      return Container.at(handle);
    }

    const Map& All() { return Container; }

  private:
    Map Container;

  };

  struct ResourceMaps {
    ResourceMap<Resources::SpriteSource> SpriteSource;
    ResourceMap<Resources::Level> Level;
  };


}

