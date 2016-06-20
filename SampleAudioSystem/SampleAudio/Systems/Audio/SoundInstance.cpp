#include "SoundInstance.h"

SoundInstance::SoundInstance(const Resources::SoundCue::Ptr cue)
  : Name(cue->getName()), Sound(cue->getSound()), Settings(cue->getSettings())
{
}

SoundInstance::~SoundInstance()
{
}

void SoundInstance::SetParameter(String parameter, Real value)
{
  Sound.SetParameter(parameter, value);
}

void SoundInstance::InterpolateVolume(Real newVolume, Real time)
{
  Settings.Volume = newVolume;
  Sound.InterpolateVolume(newVolume, time);
}

void SoundInstance::InterpolatePitch(Real newPitch, Real time)
{
  Settings.Pitch = newPitch;
  Sound.InterpolatePitch(newPitch, time);
}

void SoundInstance::Resume()
{
  Sound.Resume();
}

void SoundInstance::Pause()
{
  Sound.Pause();
}

void SoundInstance::Stop(Audio::StopMode mode)
{
  Sound.Stop(mode);
}

bool SoundInstance::IsPlaying()
{
  return Sound.IsPlaying();
}
