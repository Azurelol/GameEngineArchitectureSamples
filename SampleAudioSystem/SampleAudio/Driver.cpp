#include "Systems\Audio\Audio.h"
#include "Timer.h"

// The audio system is instantiated is either itself a singleton or
// instantiated inside one. For this demonstration it will be the former.
std::unique_ptr<Systems::Audio> AudioSystem;

//--------------------------------------------------------------------------/
// A sample interface for interfacing with the Audio System. 
// In my own engine and in DigiPen's Zero Engine they use a
// SoundSpace component in the Space for the user to do audio playback requests.
// How you choose to interface with the Audio system is up to you!
class SoundSpace {

  SoundInstance::Container ActiveInstances;

public:

  SoundInstance::Ptr PlayCue(const Resources::SoundCue::Ptr cue) {
    Trace("Playing '" + cue->getName() + "'");
    // We ask the Audio system to instantiate a SoundInstance from the given cue
    auto instance = AudioSystem->Play(cue);
    // We then add it to our container of instances (So we can keep track of them)
    ActiveInstances.push_back(instance);
    // Return a weak, non-owning ptr back to the client, since this interface
    // will take care of cleaning up these sound instances.
    return instance.get();
  }
};
std::unique_ptr<SoundSpace> Interface;

void Test1_FMOD_LowLevel();
void Test2_FMOD_Studio();

//--------------------------------------------------------------------------/
//--------------------------------------------------------------------------/

int main(void) {

  Trace("--- Sample Audio: Begin Demonstration ---");
  AudioSystem.reset(new Systems::Audio());  
  AudioSystem->Initialize();
  Interface.reset(new SoundSpace());

  std::cout << "Pick the test to run: (0,1...n) \n"
    << "1.) FMOD Low Level \n"
    << "2.) FMOD Studio \n";

  unsigned testToRun = 0;
  std::cin >> testToRun;
  switch (testToRun) {
  case 1:
    Test1_FMOD_LowLevel();
    break;
  case 2:
    Test2_FMOD_Studio();
    break;
  default:
    std::cout << "Wrong input! \n";
    break;
  }
  //--------------------------------------------------------------------------/
  // Simulate an dt-driven engine's loop
  float deltaTime = 1.0 / 60.0f;
  while (true) {
    Time::ScopeTimer frameTimer(&deltaTime);
    AudioSystem->Update(deltaTime);
  }
  //--------------------------------------------------------------------------/
  
  AudioSystem->Terminate();

  Trace("--- Sample Audio: End Demonstration ---");
  return 0;
}

void Test1_FMOD_LowLevel()
{
  Trace("");
  //--------------------------------------------------------------------------/
  // Create a SoundCue. (This would be managed by your resource manager)
  auto soundCue = Resources::SoundCue::Ptr(new Resources::SoundCue("SoundFile"));
  soundCue->setAssetPath("Assets\\SuperOrcPuncher.ogg");
  // Load the SoundCue's sound asset into memory
  AudioSystem->Add(soundCue);
  // Configure the SoundCue (This configuration would be serialized)
  auto& settings = soundCue->getSettings();
  settings.Volume = 0.5f;
  settings.Pitch = 0.9f;
  //--------------------------------------------------------------------------/
  // Request the Audio System to play it. This will instantiate a SoundInstance
  // object which settings get cloned from the original SoundCue and is told
  // to start playing by default
  auto instance = Interface->PlayCue(soundCue);
}

void Test2_FMOD_Studio()
{
  Trace("");
  // We always need to load the master bank and its accompanying "strings" bank,
  // which contains, as you guessed, string data for the bank (important for identifying events
  // by name!). Besides that, we also have to load the other banks. (Yes.. what a pain)
  std::vector<std::string> banksToLoad = { "Master Bank", "Master Bank.strings" };
  std::vector<Resources::Bank::Ptr> banks;
  
  for (auto& bankName : banksToLoad) {
    // Create a bank resource
    bankName += ".bank";
    auto bank = Resources::Bank::Ptr(new Resources::Bank(bankName));
    bank->setAssetPath("Assets\\" + bankName);
    // Load into the FMOD sound system
    AudioSystem->Add(bank);
    // Keep a reference to it for now
    banks.push_back(bank);
  }

  // After all the required banks have been loaded into the FMOD system, we can now start
  // "unpacking" them and generating events, vcas, etc...
  Resources::SoundCue::Container soundCues;
  for (auto& bank : banks) {
    // Append vectors hoho!
    // http://stackoverflow.com/questions/2551775/appending-a-vector-to-a-vector
    auto cues = bank->Generate();
    soundCues.insert(soundCues.begin(), cues.begin(), cues.end());
  }

  // Let's check what SoundCues we have now!
  Trace("SoundCues generated...");
  for (auto& soundCue : soundCues) {
    Trace("- " + soundCue->getName());
  }
  
  Trace("Now let's play one of them!");
  auto soundCue = soundCues.back();
  auto& settings = soundCue->getSettings();
  settings.Volume = 0.3f;
  auto instance = Interface->PlayCue(soundCue); 
}
