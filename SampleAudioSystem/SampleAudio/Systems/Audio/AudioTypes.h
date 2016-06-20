#pragma once

namespace Audio {

  //--------------------------------------------------------------------------/
  enum class PlayMode {
    Single,
    Loopping
  };

  enum class StopMode {
    Immediate,
    AllowFadeOut
  };

  /**************************************************************************/
  /*!
  @class PlaybackSettings A collection of audio playback settings.
  */
  /**************************************************************************/
  struct PlaybackSettings {
    PlayMode Mode;
    float Volume, VolumeVariation;
    float Pitch, PitchVariation;
    bool Loop;
    PlaybackSettings() : Mode(PlayMode::Single), Volume(1.0f), VolumeVariation(0.0f),
      Pitch(1.0f), PitchVariation(0.0f), Loop(false) {}
  };

}
