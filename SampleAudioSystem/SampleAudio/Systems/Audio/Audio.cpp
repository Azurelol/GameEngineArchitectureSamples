/******************************************************************************/
/*!
@file   Audio.cpp
@author Christian Sagel
@par    email: c.sagel\@digipen.edu
@date   5/19/2016
@brief  The abstract interface for the Audio class.
*/
/******************************************************************************/
#include "Audio.h"

namespace Systems
{
  void Audio::Initialize()
  {
    Trace("Initializing the interface!");
    Interface.Initialize();
  }

  void Audio::Update(float dt)
  {
    if (Enabled)
      Interface.Update(dt);
  }

  void Audio::Terminate()
  {
    Trace("Shutting down the interface...");
    Interface.Terminate();
  }

  /**************************************************************************/
  /*!
  @brief  Loads a SoundCue's sound file into memory.
  @param  soundCue The name of the sound file.
  */
  /**************************************************************************/
  void Audio::Add(Resources::SoundCue::Ptr soundCue)
  {
    Trace("'" + soundCue->getName() + "'");
    Interface.Add(soundCue);
  }

  void Audio::Add(Resources::Bank::Ptr bank)
  {
    Trace("'" + bank->getName() + "'");
    Interface.Add(bank);
  }

  SoundInstance::StrongPtr Audio::Play(const Resources::SoundCue::Ptr soundCue)
  {
    Trace("Playing '" + soundCue->getName() + "'");
    return Interface.Play(soundCue);
  }

}