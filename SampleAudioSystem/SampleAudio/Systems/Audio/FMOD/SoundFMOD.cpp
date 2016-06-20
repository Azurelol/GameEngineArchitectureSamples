#include "SoundFMOD.h"

#include "AudioFMOD.h"

namespace Audio
{
  void SoundFMOD::LoadParameters()
  {
    // Allocate the parameters container
    Handle.Event.Parameters = new ParametersContainer();

    // Create a temporary instance in order to retrieve the parameters    
    Handle.Event.Description->createInstance(&Handle.Event.Instance);
    // Get the number of parameters
    int parameterCount = 0;
    Systems::AudioFMOD::ErrorCheck(Handle.Event.Instance->getParameterCount(&parameterCount));
    Trace("'" + std::to_string(parameterCount) + "' parameters found!");

    if (!parameterCount) {
      return;
    }

    // Grab the parameters. We will be creating this vector to be able to retrieve them.
    std::vector<FMOD::Studio::ParameterInstance*> parameters;
    parameters.resize(static_cast<size_t>(parameterCount));
    for (int i = 0; i < parameterCount; ++i) {
      // Save an instance of the parameter
      Systems::AudioFMOD::ErrorCheck(Handle.Event.Instance->getParameterByIndex(i, &parameters[i]));
      // Record its settings and name
      FMOD_STUDIO_PARAMETER_DESCRIPTION paramDescription;
      Systems::AudioFMOD::ErrorCheck(parameters[i]->getDescription(&paramDescription));
      Handle.Event.Parameters->push_back(paramDescription);
      // Debugging
      Trace("Name: '" + std::string(paramDescription.name));
      Trace("Minimum: '" + std::to_string(paramDescription.minimum));
      Trace("Maximum: '" + std::to_string(paramDescription.maximum));
      Trace("Type: '" + std::to_string(paramDescription.type));
    }

    // Clean up the temporary instance
    Handle.Event.Instance->release();
    Handle.Event.Instance->stop(FMOD_STUDIO_STOP_IMMEDIATE);
  }

  void SoundFMOD::SetParameter(const std::string & parameter, float value)
  {
    if (Type == Type::Event && Handle.Event.Instance)
      Handle.Event.Instance->setParameterValue(parameter.c_str(), value);
  }

  void SoundFMOD::InterpolateVolume(float newVolume, float time)
  {
    if (Type == Type::Event && Handle.Event.Instance) {
      if (time > 0.0f) {
        Trace("Interpolation is not implemented yet!");
      }
      else
        Handle.Event.Instance->setVolume(newVolume);
    }
    else if (Type == Type::File && Handle.Sound.Channel) {
      if (time > 0.0f) {
        Trace("Interpolation is not implemented yet!");
      }
      else
        Handle.Sound.Channel->setVolume(newVolume);
    }
  }

  void SoundFMOD::InterpolatePitch(float newPitch, float time)
  {
    if (Type == Type::Event && Handle.Event.Instance) {
      if (time > 0.0f) {
        Trace("Interpolation is not implemented yet!");
      }
      else
        Handle.Event.Instance->setPitch(newPitch);
    }
    else if (Type == Type::File && Handle.Sound.Channel) {
      if (time > 0.0f) {
        Trace("Interpolation is not implemented yet!");
      }
      else
        Handle.Sound.Channel->setPitch(newPitch);
    }
  }

  void SoundFMOD::Resume()
  {
    if (Type == Type::Event && Handle.Event.Instance)
      Handle.Event.Instance->setPaused(false);
    else if (Type == Type::File && Handle.Sound.Channel)
      Handle.Sound.Channel->setPaused(false);
  }

  void SoundFMOD::Pause()
  {
    if (Type == Type::Event && Handle.Event.Instance)
      Handle.Event.Instance->setPaused(true);
    else if (Type == Type::File && Handle.Sound.Channel)
      Handle.Sound.Channel->setPaused(true);
  }

  void SoundFMOD::Stop(Audio::StopMode mode)
  {
    if (Type == Type::Event && Handle.Event.Instance) {
      switch (mode) {
      case StopMode::Immediate:
        Handle.Event.Instance->stop(FMOD_STUDIO_STOP_IMMEDIATE);
        break;
      case StopMode::AllowFadeOut:
        Handle.Event.Instance->stop(FMOD_STUDIO_STOP_ALLOWFADEOUT);
        break;
      }
    }
    else if (Type == Type::File && Handle.Sound.Channel)
      Handle.Sound.Channel->stop();
  }

  bool SoundFMOD::IsPlaying()
  {
    bool paused;
    if (Type == Type::Event && Handle.Event.Instance) {
      Handle.Event.Instance->getPaused(&paused);
      return paused;
    }
    else if (Type == Type::File && Handle.Sound.Channel) {
      Handle.Sound.Channel->getPaused(&paused);
      return paused;
    }
  }
}