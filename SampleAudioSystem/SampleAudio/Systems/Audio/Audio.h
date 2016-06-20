/******************************************************************************/
/*!
@file   Audio.h
@author Christian Sagel
@par    email: c.sagel\@digipen.edu
@date   5/19/2016
@brief  The abstract interface for the Audio class.
*/
/******************************************************************************/
#pragma once
#include "..\System.h"

// Resources
#include "..\..\Resources\Audio\SoundCue.h"
#include "..\..\Resources\Audio\Bank.h"
#include "SoundInstance.h"
//#include "..\..\Components\Audio\SoundSpace.h"
// Interface
#include "FMOD\AudioFMOD.h"

namespace Systems
{
  class Audio : public System {

    AudioFMOD Interface;
    bool Enabled;

  public:

    Audio() : System("Audio"), Enabled(true) {}
    void Initialize();
    void Update(float dt);
    void Terminate();

    void Add(Resources::SoundCue::Ptr soundCue);
    void Add(Resources::Bank::Ptr bank);
    SoundInstance::StrongPtr Play(const Resources::SoundCue::Ptr soundCue);



  };

}