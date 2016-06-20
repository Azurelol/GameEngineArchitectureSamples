
// STL
#include <iostream>
#include <fstream>
#include <cstdio>
#define Trace(message) std::cout << message << "\n"

// The watcher
#include "DirectoryWatcher.h"

// Wait function
void Wait(int sec) {
  std::this_thread::sleep_for(std::chrono::seconds(sec));
}

// Callback function
void OnDirectoryWatchEvent(DirectoryWatcher::Event fileEvent, const FileInfo& info) {

  switch (fileEvent) {
  case DirectoryWatcher::Event::FileFound:
    Trace(info.Name + " was found!");
    break;

  case DirectoryWatcher::Event::FileMoved:
    Trace(info.Name + " was moved!");
    break;

  case DirectoryWatcher::Event::FileUpdated:
    Trace(info.Name + " was updated!");
    break;

  case DirectoryWatcher::Event::FileDeleted:
    Trace(info.Name + " was deleted!");
    break;
  }
}

int main(void) {

  Trace("Directory Watcher Demonstration:");
  std::string dirPath = "VeryImportantFolder\\";
  std::string testFileName = dirPath + "WowMuchScan.doge";

  // Note: Due to the way it's threaded if you pause with breakpoints the messages may go out of order.
  //--------------------------------------------------------------------------/
  Trace("Let's start by instantiating the DirectoryWatcher object and point it at the directory");  // We first construct a configuration object then set its members to our liking
  DirectoryWatcher::Config settings;
  settings.Frequency = 1;  // How often to scan
  settings.Path = dirPath; // The directory which to scan
  // We then pass it to the constructor of the directory watcher. This is quite an useful pattern for OOP
  DirectoryWatcher watcher(settings);
  // Now, here's where we can get clever. Let's create a callback function of our own
  // so that the directory watcher can inform us when it detects a change in the directory. 
  watcher.Subscribe(&OnDirectoryWatchEvent);
  // Let's initialize it
  watcher.Initialize();
  //--------------------------------------------------------------------------/
  Trace("2. Let's run the first test. Let's create a file!");
  std::ofstream testFile(testFileName);
  if (!testFile) {
    Trace("Couldn't create the file???");
    exit(-1);
  }
  testFile.close();
  // Let's wait so the directory watcher can.. you know.. scan
  Wait(settings.Frequency + 1);
  //--------------------------------------------------------------------------/
  Trace("3. Now let's modify that file!");
  testFile.open(testFileName, std::ofstream::in);
  testFile << "Such write much wow";
  testFile.close();
  Wait(settings.Frequency + 1);
  //--------------------------------------------------------------------------/
  Trace("4. Now let's delete it!");
  std::remove(testFileName.c_str());
  Wait(settings.Frequency + 1);

  return 0;

}