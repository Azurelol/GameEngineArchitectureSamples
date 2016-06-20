#include "Content.h"

namespace Systems {

  std::unique_ptr<Content> ContentSystem;

  Content::Content() : System("Content")
  {
  }

  void Content::Initialize()
  {
  }

  void Content::Update(float dt)
  {
  }

  void Content::Terminate()
  {
  }

  ResourceMaps & Content::Resources()
  {
    return AllResources;
  }

}