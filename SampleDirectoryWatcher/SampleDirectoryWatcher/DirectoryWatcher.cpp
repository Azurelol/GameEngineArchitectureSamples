#include "DirectoryWatcher.h"

DirectoryWatcher::DirectoryWatcher(const Config & settings) 
  : Settings(settings), ScanHistory(new DirectoryScan())
{
  
}

DirectoryWatcher::~DirectoryWatcher()
{
  Active = false;
  if (ScanThread.joinable()) ScanThread.join();
  delete ScanHistory;
}

void DirectoryWatcher::Initialize()
{  
  // Scan the first time on the main thread
  Scan();
  // Start the file-scanning thread
  ScanThread = std::thread(&DirectoryWatcher::RunThreadScan, this);
}

void DirectoryWatcher::RunThreadScan()
{
  Active = true;
  try {
    while (Active) {
      Scan();
      std::this_thread::sleep_for(std::chrono::seconds(Settings.Frequency));
    }
  }
  // Implement your own exception here ~_~
  catch (...) {

  }
}

void DirectoryWatcher::Announce(Event event, const FileInfo & info)
{
  // Let's call the function for every subscriber!
  for (auto& fn : Subscribers) {
    fn(event, info);
  }
}

void DirectoryWatcher::Resume()
{
  RunThreadScan();
}

void DirectoryWatcher::Pause()
{
  Active = false;
}

void DirectoryWatcher::Subscribe(Callback fn)
{
  Subscribers.push_back(fn);
}

void DirectoryWatcher::Scan()
{
  // Let's get the absolute path of the specified directory
  FilePath scanPath = fs::current_path().string() + "\\" + Settings.Path;

  // Check if it exists!
  if (!fs::exists(scanPath))
    return;

  // Let's create a new scan object
  auto currentScan = new DirectoryScan();
  // Create the recursive directory iterators
  fs::recursive_directory_iterator dirIter(scanPath), end;

  // Scan the current directory
  while (dirIter != end) {
    FilePath path = dirIter->path();
    if (fs::is_regular_file(path))
    {
      // Grab file info
      FileInfo info(path);

      // Grab a reference to the index in the map.
      FileInfo& scanRef = (*currentScan)[info.Name];

      /* NOTE: Map subscript operators create elements if they don't exist,
      so we check for the default value of 'LastModified' */

      // If it already existed, it means we are trying to insert a filename twice,
      // when it should be unique. Unacceptable.
      if (scanRef.LastModified != 0) {
        //throw("Unacceptable!");
      }

      // If it did not exist yet, we can safely insert via reference.
      scanRef = info;
    }
    ++dirIter;
  }

  ScanIter oldIt = ScanHistory->begin(), oldEnd = ScanHistory->end();
  ScanIter newIt = currentScan->begin(), newEnd = currentScan->end();

  // 2. We now have an old scan and a new one. Because both are ordered maps, we can walk them together
  //    When files exist in both, we send according events
  while (oldIt != oldEnd && newIt != newEnd)
  {
    // a.) If the file still exists...
    if (oldIt->first == newIt->first)
    {
      // If the file was moved...
      if (oldIt->second.AbsolutePath != newIt->second.AbsolutePath) {
        Announce(Event::FileMoved, newIt->second);
      }
      // If the file was modified...
      else if (oldIt->second.LastModified != newIt->second.LastModified) {
        Announce(Event::FileUpdated, newIt->second);
      }
      // Otherwise the file is the same..
      // Move both scans forward one element
      ++oldIt;
      ++newIt;
    }

    // b.) If the new scan contains files new files
    else if (oldIt->first > newIt->first)
    {
      Announce(Event::FileFound, newIt->second);
      ++newIt;
    }
    // c.) If the new scan is further along, and old has files that new did not, means the were deleted
    else
    {
      Announce(Event::FileDeleted, oldIt->second);
      ++oldIt;
    }
  }
  // 3. Any files left in oldIt must have been deleted
  while (oldIt != oldEnd) {
    Announce(Event::FileDeleted, oldIt->second);
    ++oldIt;
  }
  // 4. Any files left in newIt must be new
  while (newIt != newEnd) {
    Announce(Event::FileFound, newIt->second);
    ++newIt;
  }

  // Now that we are done with the current scan, store the new data as the historical data
  if (ScanHistory)
    delete ScanHistory;

  ScanHistory = currentScan;

}


