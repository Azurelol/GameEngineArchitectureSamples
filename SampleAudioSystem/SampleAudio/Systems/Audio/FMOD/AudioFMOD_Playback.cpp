#include "AudioFMOD.h"

namespace Systems {
 
  /**************************************************************************/
  /*!
  @brief Plays a sound through FMOD LowLevel API.
  @param soundPtr A pointer to the Sound data.
  @param channel  A pointer to the Channel handle.
  @param loop Whether the sound should be played in a loop.
  @param volume The volume at which to play the sound.
  @param pitch The pitch of the sound.
  @return True if successful, false otherwise.
  */
  /**************************************************************************/
  bool AudioFMOD::Play(FMOD::Sound * address, FMOD::Channel ** channel, bool loop, float volume, float pitch)
  {
    Trace("");    

    auto result = ErrorCheck(System.LowLevel->playSound(address, nullptr, false, channel));

    // Set the loop, volume and pitch    
    if (loop) {
      (*channel)->setMode(FMOD_LOOP_NORMAL);
      (*channel)->setLoopCount(-1);
    }
    else {
      (*channel)->setMode(FMOD_LOOP_OFF);
    }
    (*channel)->setVolume(volume);
    (*channel)->setPitch(pitch);

    // Have it release when it's done playing
    // address->release();

    return result;
  }

  /**************************************************************************/
  /*!
  @brief Plays a sound through FMOD Studio API once.
  @param description The description of the event (name, address, etc)
  @param channel  A pointer to the Channel handle.
  @param loop Whether the sound should be played in a loop.
  @param volume The volume at which to play the sound.
  @param pitch The pitch of the sound.
  @return True if successful, false otherwise.
  */
  /**************************************************************************/
  bool AudioFMOD::Play(FMOD::Studio::EventDescription* description, FMOD::Studio::EventInstance ** instance, bool loop, float volume, float pitch)
  {
    Trace("");

    // Create the instance off the decription
    if (!ErrorCheck(description->createInstance(instance)))
      return false;
    
    // Configure it
    (*instance)->setVolume(volume);
    (*instance)->setPitch(pitch);
    (*instance)->start();

    // Have it release when it's done playing
    // (*instance)->release();

    return true;
  }

}