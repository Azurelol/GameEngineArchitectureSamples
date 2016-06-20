/*****************************************************************************/
/*!
@file      BankFMOD.cpp
@author    Christian Sagel
@par       email: c.sagel\@digipen.edu
@date      5/22/2016
@brief     The implementation details for a bank in FMOD.
*/
/******************************************************************************/
#include "BankFMOD.h"

// For debugging routines
#include "AudioFMOD.h"

/**************************************************************************/
/*!
@brief  Loads all event descriptions from a bank, loading them onto memory
        and adding their identifiers to the common map.
*/
/**************************************************************************/
void Audio::BankFMOD::LoadEventDescriptions()
{ 

  int eventCount = 0;
  if (!Systems::AudioFMOD::ErrorCheck(Address->getEventCount(&eventCount)))  {
    Trace("No events found!");
    return;
  }

  int eventsReturned = 0;
  FMOD::Studio::EventDescription ** eventList = (FMOD::Studio::EventDescription **)malloc(eventCount * sizeof(void *));
  if (!Systems::AudioFMOD::ErrorCheck(Address->getEventList(eventList, eventCount, &eventsReturned))) {
    Trace("No events retrieved!");
    return;
  }

  Trace("Loading '" + std::to_string(eventsReturned) + "' events");
  for (int i = 0; i < eventsReturned; ++i)
  {
    int buff_sz = 0;
    char path[256] = { 0 };
    Systems::AudioFMOD::ErrorCheck(eventList[i]->getPath(path, 255, &buff_sz));
    //printf("%s\n", path);

    // I heavily recommend to **really** use a filesystem library to extract the name of 
    // the event rather than use the full path :)
    //auto name = FileSystem::FileNoExtension(path);
    std::string name = path;
    Trace("- " + name);
    AvailableEvents.insert(std::pair<const Handle, FMOD::Studio::EventDescription*>(name, eventList[i]));
  }
}

/**************************************************************************/
/*!
@brief Loads all VCAs from the bank. This will add them to a container
       of VCA objects held inside the bank object.
*/
/**************************************************************************/
void Audio::BankFMOD::LoadVCAs()
{
  int count;
  if (!Systems::AudioFMOD::ErrorCheck(Address->getVCACount(&count))) {
    Trace("No VCAs found!");
  return;
  }

  int vcasFound;
  FMOD::Studio::VCA ** vcaList = (FMOD::Studio::VCA **)malloc(count * sizeof(void *));
  if (!Systems::AudioFMOD::ErrorCheck(Address->getVCAList(vcaList, count, &vcasFound)))
    return;

  Trace("'" + std::to_string(vcasFound) + "'' VCAs found!");

  for (int i = 0; i < vcasFound; ++i) {
    // Grab the path of the VCA
    int buff_sz = 0;
    char path[256] = { 0 };
    Systems::AudioFMOD::ErrorCheck(vcaList[i]->getPath(path, 255, &buff_sz));
    // Extract the name of the VCA
    std::string name = path;
    //auto name = FileSystem::FileNoExtension(path);

    // Add it to the container
    Trace("Added '" + name + "'");
    auto vca = VCA(vcaList[i]);
    ActiveVCAs.insert(std::pair<Handle, VCA>(name, vca));
  }
}

/**************************************************************************/
/*!
@brief Loads all buses from the bank.
*/
/**************************************************************************/
void Audio::BankFMOD::LoadBuses()
{
}

/**************************************************************************/
/*!
@brief  Unpacks and generates the resources contained inside a bank:
        Events, VCAs, Buses, etc... In addition it will generate SoundCues
        from the list of events that can be used.
*/
/**************************************************************************/
Resources::SoundCue::Container  Audio::BankFMOD::Generate()
{
  LoadEventDescriptions();
  LoadVCAs();
  LoadBuses();

  Resources::SoundCue::Container soundCues;
  for (auto& event : AvailableEvents) {
    // Create the SoundCue
    auto soundCue = Resources::SoundCue::Ptr(new Resources::SoundCue(event.first));
    // Set what kind of SoundCue it is!
    soundCue->getSound().Type = Audio::Sound::Type::Event;
    // Set its event description
    soundCue->getSound().Handle.Event.Description = event.second;
    // Retrieve its parameters
    soundCue->getSound().LoadParameters();

    soundCues.push_back(soundCue);
  }

  return soundCues;
}
