#pragma once
#include "../Object/System.h"

#include "ResourceMap.h"

namespace Systems {

  class Content : public System {

    ResourceMaps AllResources;

  public:
    Content();
    void Initialize();
    void Update(float dt);
    void Terminate();
    ResourceMaps& Resources();

  };

  // Single instance of the system
  extern std::unique_ptr<Content> ContentSystem;

}

