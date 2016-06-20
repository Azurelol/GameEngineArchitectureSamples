#include "AudioFMOD.h"

namespace Systems
{
  /**************************************************************************/
/*!
@brief Checks for FMOD errors.
@param result The result of an FMOD function call.
*/
/**************************************************************************/
  bool AudioFMOD::ErrorCheck(FMOD_RESULT result) {
    if (result != FMOD_OK) {
      Trace("FMOD error! (" + std::to_string(result) + ")"
        + FMOD_ErrorString(result) + "\n");
      return false;
    }
    return true;
  }

  /**************************************************************************/
  /*!
  @brief  Initializes FMOD's Low Level and Studio systems.
  */
  /**************************************************************************/
  void AudioFMOD::Initialize()
  {
    Trace("Initializing Low Level and Studio system objects... ");
    // Create the Low Level System
    ErrorCheck(FMOD::System_Create(&System.LowLevel));
    // Create the Studio System
    ErrorCheck(System->create(&System.Studio));
    // Set FMOD low level studio pointer
    ErrorCheck(System->getLowLevelSystem(&System.LowLevel));
    // Initialize it
    unsigned maxChannels = 36;
    ErrorCheck(System->initialize(maxChannels, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, nullptr));
  }

  /**************************************************************************/
  /*!
  @brief Updates FMOD's Low Level and Studio systems.
  @param dt The delta time.
  */
  /**************************************************************************/
  void AudioFMOD::Update(float dt) {
    // Update the low level API system
    ErrorCheck(System.LowLevel->update());
    // Update the 'Studio' API system
    ErrorCheck(System.Studio->update());
  }

  /**************************************************************************/
  /*!
  @brief  Terminates the FMOD systems.
  */
  /**************************************************************************/
  void AudioFMOD::Terminate()
  {
  }

  //--------------------------------------------------------------------------/
  //--------------------------------------------------------------------------/

  void AudioFMOD::Add(Resources::SoundCue::Ptr soundCue)
  {
    Trace("'" + soundCue->getName() + "'");
    soundCue->getSound().Type = ::Audio::Sound::Type::File;
    auto& soundAddress = soundCue->getSound().Handle.Sound.File;
    auto& soundFile = soundCue->getAssetPath();
    //auto& soundAddress = soundCue->getSound().Address;

    // You pick which to use depending on file size here.
    // For now, we will be using stream.
    CreateStream(soundFile, &soundAddress);
    //CreateSound(soundFile, &soundAddress);
  }

  void AudioFMOD::Add(Resources::Bank::Ptr bank)
  {
    Trace("'" + bank->getName() + "'");
    auto& internal = bank->getInternal();
    Load(internal->Address, bank->getAssetPath());   
    // Keep track of it. Later on when the client tries to play events, or access 
    // vca/buses they can go through the containers of banks for them!
    ActiveBanks.push_back(internal);
    // Load the event descriptions
    //internal->LoadEventDescriptions();
    // Load channel groups
    
    // Load VCAs

    // Load Buses

  }

  SoundInstance::StrongPtr AudioFMOD::Play(const Resources::SoundCue::Ptr soundCue)
  {
    auto instance = SoundInstance::StrongPtr(new SoundInstance(soundCue));
    auto& sound = instance->getSound();
    auto& settings = instance->getSettings();

    // (!) An alternate way to differentiate between what type it is could be to just check
    // whether the pointers are null!

    // FMOD Low Level
    if (sound.Type == ::Audio::Sound::Type::File) {
      Play(sound.Handle.Sound.File, &(sound.Handle.Sound.Channel), settings.Loop, settings.Volume, settings.Pitch);
    }
    // FMOD Studio
    else if (sound.Type == ::Audio::Sound::Type::Event) {
      Play(sound.Handle.Event.Description, &sound.Handle.Event.Instance, settings.Loop, settings.Volume, settings.Pitch);
    }

    return instance;
  }

}