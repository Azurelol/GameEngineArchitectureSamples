#pragma once

#include <FMOD\fmod.hpp>
#include <FMOD\fmod_studio.hpp>

#include <string>
#include <vector>
#include "..\AudioTypes.h"

namespace Audio {
  
  class SoundFMOD {
  public:

    // A given sound from FMOD can originate either directly from a sound file
    // and loaded via an FMOD::Sound* or created from an FMOD::Studio::EventDescription*
    // from a given bank. Due to this we have to find some way to separate these two types
    // since a sound can only come from one or the other, and their methods and members
    // are different. Here I did quick but perhaps you may want to use an OOP approach
    // and use inheritance to solve the issue~
    //------------------------------------------------------------------------/
    enum class Type {
      File,
      Event
    };

    using ParametersContainer = std::vector<FMOD_STUDIO_PARAMETER_DESCRIPTION>;    
    struct Event {
      FMOD::Studio::EventDescription* Description;
      FMOD::Studio::EventInstance* Instance;
      ParametersContainer* Parameters;
    };

    struct Sound {
      FMOD::Sound* File;
      FMOD::Channel* Channel;
    };

    union Handle {
      Event Event;
      Sound Sound;      
    };        
    //------------------------------------------------------------------------/

    Type Type;
    Handle Handle;

    ~SoundFMOD() {
      if (Type == Type::Event)
        delete Handle.Event.Parameters;
    }
    void LoadParameters();
    void SetParameter(const std::string& parameter, float value);
    void InterpolateVolume(float newVolume, float time = 0.0f);
    void InterpolatePitch(float newPitch, float time = 0.0f);
    void Resume();
    void Pause();
    void Stop(Audio::StopMode mode = Audio::StopMode::AllowFadeOut);
    bool IsPlaying();

  };
}

