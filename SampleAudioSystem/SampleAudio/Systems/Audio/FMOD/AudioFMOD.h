#pragma once

#include <FMOD\fmod.hpp>
#include <FMOD\fmod_studio.hpp>
#include <FMOD\fmod_errors.h>

#include "..\..\Trace.h"

// Audio resources
#include "..\..\Resources\Audio\SoundCue.h"
#include "..\..\Resources\Audio\Bank.h"
#include "..\SoundInstance.h"

namespace Systems
{
  class AudioFMOD {

    class SystemPtr {
    public:
      FMOD::Studio::System* Studio;
      FMOD::System* LowLevel;
      SystemPtr() : Studio(nullptr), LowLevel(nullptr) {
        //if (FMOD::System_Create(&LowLevel) != FMOD_OK) {        
        //}

      }

      ~SystemPtr() {
        LowLevel->release();
        Studio->release();
      }

      SystemPtr(SystemPtr&&) = default;
      SystemPtr& operator=(SystemPtr&&) = default;
      SystemPtr(const SystemPtr&) = delete;
      SystemPtr& operator=(const SystemPtr&) = delete;
      FMOD::Studio::System* operator->() { return Studio; }

    };

    SystemPtr System;

    // Banks
    ::Audio::BankFMOD::Container ActiveBanks;
    bool Load(FMOD::Studio::Bank*& bank, const std::string& path);
    // Create
    bool CreateSound(const std::string& soundFile, FMOD::Sound** soundPtr);
    bool CreateStream(const std::string& soundFile, FMOD::Sound** soundPtr);
    FMOD::Studio::EventInstance* CreateEventInstance(FMOD::Studio::EventDescription* event) const;
    // Playback
    bool Play(FMOD::Sound* address, FMOD::Channel** channel, bool loop, float volume, float pitch);
    bool Play(FMOD::Studio::EventDescription*, FMOD::Studio::EventInstance** instance, bool loop, float volume, float pitch);

  public:

    void Initialize();
    void Update(float dt);
    void Terminate();

    // Interface
    static bool ErrorCheck(FMOD_RESULT result);
    void Add(Resources::SoundCue::Ptr soundCue);
    void Add(Resources::Bank::Ptr bank);
    SoundInstance::StrongPtr Play(const Resources::SoundCue::Ptr soundCue);


  };
}