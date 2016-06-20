#pragma once

// STL
#include <string>
#include <vector>
#include <functional>
#include <map>
#include <thread>
#include <chrono>
#include "FileInfo.h"

class DirectoryWatcher {

public:

  //--------------------------------------------------------------//
  struct Config {
    std::string Path;   // The path of the directory which to scan
    unsigned Frequency; // How often to scan for (in seconds)
    Config() : Frequency(10) {}
  };
  //--------------------------------------------------------------//
  enum class Event {
    FileMoved,
    FileUpdated,
    FileFound,
    FileDeleted
  };
  //--------------------------------------------------------------//  
  //--------------------------------------------------------------//
  using DirectoryScan = std::map<std::string, FileInfo>;
  using ScanPair = std::pair<std::string, FileInfo>;
  using ScanIter = std::map<std::string, FileInfo>::const_iterator;
  using Callback = std::function<void(Event, const FileInfo& info)>;
  //--------------------------------------------------------------//;



  //--------------------------------------------------------------//
  
  DirectoryWatcher(const Config& settings);
  ~DirectoryWatcher();
  void Initialize();
  void Resume();
  void Pause();
  void Subscribe(Callback fn);

private:

  bool Active;
  Config Settings;
  std::thread ScanThread;
  DirectoryScan* ScanHistory;
  std::vector<Callback> Subscribers;

  void RunThreadScan();
  void Scan();
  void Announce(Event event, const FileInfo& info);





};