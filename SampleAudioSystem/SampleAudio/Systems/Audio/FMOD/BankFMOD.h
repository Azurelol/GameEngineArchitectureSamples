/*****************************************************************************/
/*!
@file      BankFMOD.h
@author    Christian Sagel
@par       email: c.sagel\@digipen.edu
@date      5/22/2016
@brief     The implementation details for a bank in FMOD.
*/
/******************************************************************************/
#pragma once

#include <FMOD\fmod.hpp>
#include <FMOD\fmod_studio.hpp>

#include <string>
#include <memory>
#include <vector>
#include <map>

#include "..\..\Trace.h"

#include "..\..\..\Resources\Audio\SoundCue.h"

namespace Audio {

  struct VCA {

    using Handle = std::string;
    using Data = FMOD::Studio::VCA*;
    using Ptr = VCA*;
    using Container = std::map<Handle, VCA>;

    Handle Name;
    Data Address;

    VCA(Data address) : Address(address) {}
    static VCA::Ptr Find(const std::string& name);
    void setFaderLevel(const float&);
    const float& getFaderLevel();

  };

  struct BankFMOD {

    using Handle = std::string;
    using Ptr = std::shared_ptr<BankFMOD>;
    using Container = std::vector<Ptr>;
    using Data = FMOD::Studio::Bank;
    using EventDescriptions = std::map<Handle, FMOD::Studio::EventDescription*>;
    //using Buses = std::map<Handle, FMOD::Studio::Bus*>;
    //using VCAs = std::map<Handle, FMOD::Studio::VCA*>;

    Handle Name;
    Data* Address;
    EventDescriptions AvailableEvents;
    VCA::Container ActiveVCAs;
    
    Resources::SoundCue::Container Generate();
    void LoadEventDescriptions();
    void LoadVCAs();
    void LoadBuses();

  };

}


