#include "AudioFMOD.h"

namespace Systems {


  /**************************************************************************/
  /*!
  @brief  Loads a bank to the FMOD Studio system.
  @param  bank The handle to be used to access the bank.
  @param  path The filepath where the bank is located.
  @return The success of the operation.
  */
  /**************************************************************************/
  bool AudioFMOD::Load(FMOD::Studio::Bank*& bank, const std::string & path)
  {
    Trace("Loading '" + path + "'");
    // Load the bank into the sound system
    if (!ErrorCheck(System->loadBankFile(path.c_str(), FMOD_STUDIO_LOAD_BANK_NORMAL, &bank)))
      return false;

    // Now that the bank is finished loading, load its sample data
    ErrorCheck(bank->loadSampleData());
    return true;
  }

  /**************************************************************************/
  /*!
  @brief  Loads a sound into memory in its entirety, decompressing it if
          necessary.
  */
  /**************************************************************************/
  bool AudioFMOD::CreateSound(const std::string & soundFile, FMOD::Sound ** soundPtr)
  {
    Trace("Loaded '" + soundFile + "' into memory");
    return ErrorCheck(System.LowLevel->createSound(soundFile.c_str(), FMOD_CREATESAMPLE, 0, soundPtr));
  }

  /**************************************************************************/
  /*!
  \brief  Opens a file and buffers it a piece at a time, decompressing each
  bufferred segment on the fly during playback.
  */
  /**************************************************************************/
  bool AudioFMOD::CreateStream(const std::string & soundFile, FMOD::Sound ** soundPtr)
  {
    Trace("Buffering '" + soundFile + "'");
    return ErrorCheck(System.LowLevel->createStream(soundFile.c_str(), FMOD_DEFAULT, 0, soundPtr));
  }

  FMOD::Studio::EventInstance * AudioFMOD::CreateEventInstance(FMOD::Studio::EventDescription * event) const
  {
    FMOD::Studio::EventInstance* instance;
    event->createInstance(&instance);
    return instance;
  }



}