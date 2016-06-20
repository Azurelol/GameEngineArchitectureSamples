/*****************************************************************************/
/*!
@file      SoundInstance.h
@author    Christian Sagel
@par       email: c.sagel\@digipen.edu
@date      5/19/2016
@brief     SoundInstance is an object created whenever a SoundCue is played that
           acts as the particular instance of that playing of the SoundCue as well
           as a direct representation of the sound currently playing.
           The SoundInstance object is only created through code.
*/
/******************************************************************************/
#pragma once
#include "..\..\Resources\Audio\SoundCue.h"


class SoundInstance {
  
  std::string Name;
  Audio::PlaybackSettings Settings;
  Audio::Sound Sound;

public:

  void SetParameter(String parameter, Real value);
  void InterpolateVolume(Real newVolume, Real time);
  void InterpolatePitch(Real newPitch, Real time);
  void Resume();
  void Pause();
  void Stop(Audio::StopMode mode = Audio::StopMode::AllowFadeOut);
  bool IsPlaying();

  SoundInstance(const Resources::SoundCue::Ptr);
  ~SoundInstance();
  Audio::Sound& getSound() { return Sound; }
  DEFINE_PROPERTY(std::string, Name);
  DEFINE_PROPERTY(Audio::PlaybackSettings, Settings);

  using Ptr = SoundInstance*;
  using StrongPtr = std::shared_ptr<SoundInstance>;
  using Container = std::vector<StrongPtr>;

};