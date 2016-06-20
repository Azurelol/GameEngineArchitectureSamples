#pragma once
#include "..\Resource.h"

#include "Sound.h"

namespace Resources
{  
  /**************************************************************************/
  /*!
  @class SoundCue Encapsulates sound data.
  */
  /**************************************************************************/
  class SoundCue : public Resource {
    Audio::PlaybackSettings Settings;
    Audio::Sound Sound;
  public:
    //------------------------------------------------------------------------/
    using Ptr = std::shared_ptr<SoundCue>;
    using Container = std::vector<Ptr>;
    //------------------------------------------------------------------------/
    SoundCue(std::string name);
    Audio::PlaybackSettings& getSettings() { return Settings; }
    Audio::Sound& getSound() { return this->Sound; }

  };
}