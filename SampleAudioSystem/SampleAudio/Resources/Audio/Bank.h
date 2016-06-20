/*****************************************************************************/
/*!
@file      Bank.h
@author    Christian Sagel
@par       email: c.sagel\@digipen.edu
@date      5/22/2016
*/
/******************************************************************************/
#pragma once
#include "..\Resource.h"

// Banks generate SoundCues of their own
#include "SoundCue.h"

// Interface: FMOD
#include "..\..\Systems\Audio\FMOD\BankFMOD.h"

namespace Resources {

  class Bank : public Resource {

    Audio::BankFMOD::Ptr Interface;

  public:

    using Ptr = std::shared_ptr<Bank>;
    using Container = std::vector<Ptr>;

    Bank(const std::string& name) : Resource(name) { Interface.reset(new Audio::BankFMOD()); }
    Audio::BankFMOD::Ptr& getInternal() { return this->Interface; }
    SoundCue::Container Generate();

  };

}
