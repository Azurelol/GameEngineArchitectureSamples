#pragma once

#include <ctime>
#include <experimental\filesystem>

namespace fs = std::experimental::filesystem;
using FilePath = fs::path;

struct FileInfo {

  std::string AbsolutePath;   // The absolute path of the file
  std::string Name;           //                        Example: foo.bar
  std::string Stem;           // Basename of the file.  Example: foo
  std::string Extension;      // Extension of the file. Example: bar
  std::time_t LastModified;

  // Let's provide several constructors!
  FileInfo() : LastModified(0) {}

  FileInfo(const FilePath& path) : AbsolutePath(path.string()),
                                   Name(path.filename().string()),
                                   Stem(path.stem().string()),
                                   Extension(path.extension().string()) 
  {
    // Last Modified (Normally this would be a method provided by a filesystem interface)
    fs::file_time_type time = fs::last_write_time(path);
    LastModified = decltype(time)::clock::to_time_t(time);
  }

  FileInfo(const std::string& path) 
  {
    FilePath pathObj = path;

    AbsolutePath = pathObj.string();
    Name = pathObj.filename().string();
    Stem = pathObj.filename().stem().string();
    Extension = pathObj.extension().string();

    // Last Modified (Normally this would be a method provided by a filesystem interface)
    fs::file_time_type time = fs::last_write_time(pathObj);
    LastModified = decltype(time)::clock::to_time_t(time);
  }
    

};