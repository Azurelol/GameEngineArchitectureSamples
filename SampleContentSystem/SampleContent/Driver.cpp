#include "Content\Content.h"

int main(void) {

  // Instantiate the content system
  Trace("Instantiating the Content System");
  Systems::ContentSystem.reset(new Systems::Content());
  // Add a few resources to it through the interface.
  // Normally we would scan a folder of resource files (which hold serialized
  // data regarding what assets they point to, what type of resource they are),
  // then depending on their extensions or some identifier we would add them
  // to the content system into containers of distinct categories (sprites, soundcues, etc)
 
  // For this demonstration I will just construct it here
  Resources::SpriteSource::StrongPtr spritey(new Resources::SpriteSource("Spritey", "Resources\\Spritey.SpriteSource"));
  Trace("Constructed the SpriteSource resource '" + spritey->getName() + "'");
  // Add it to the Content system
  Systems::ContentSystem->Resources().SpriteSource.Add(spritey);
  Trace("Added '" + spritey->getName() + "' to the Content system.");
  // Let's see if it was added by checking the count
  auto& sprites = Systems::ContentSystem->Resources().SpriteSource;  
  Trace("The SpriteSource map has '" + std::to_string(sprites.All().size()) + "' elements!");
  
  // A. Retrieve them through the content system directly...
  auto spriteyRef1 = Systems::ContentSystem->Resources().SpriteSource.Find("Spritey");
  // B. Or through a  static "Find" method each resource should have!
  auto spriteyRef2 = Resources::SpriteSource::Find("Spritey");

  // Now let's remove it from the container
  Trace("Now removing '" + spritey->getName() + "'");
  Systems::ContentSystem->Resources().SpriteSource.Remove("Spritey");
  Trace("The SpriteSource map now has '" + std::to_string(sprites.All().size()) + "' elements!");

  return 0;


}