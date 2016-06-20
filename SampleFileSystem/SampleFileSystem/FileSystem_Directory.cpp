/*!****************************************************************************\
@file   FileSystem_Directory.cpp
@author Christian Sagel
@date   5/29/2016
@brief  Provides facilities for performing operations on file systems and their
components, such as paths, regular files, and directories.
@note   References:
http://en.cppreference.com/w/cpp/experimental/fs
https://msdn.microsoft.com/en-us/library/hh874694.aspx

\******************************************************************************/
#include "FileSystem.h"

namespace fs = std::experimental::filesystem;

namespace Systems {

  /*!************************************************************************\
  @brief  Retrieves the path of the current directory.
  @return The path of the current directory.
  \**************************************************************************/
  FileSystem::Path FileSystem::DirectoryCurrent()
  {
    return fs::current_path().string();
  }

  /*!************************************************************************\
  @brief  Lists all the file names in the given directory path.
  @param  dirPath The path of the directory.
  @param  files A vector of strings, to contain the names of the files.
  @param  hasPath Whether the path in each file should be included or not.
  @return The string vector, containing all the files with their path.
  \**************************************************************************/
  FileSystem::PathList FileSystem::DirectoryListFiles(const Path & dirPath, bool hasPath)
  {
    FileSystem::PathList files;

    if (Exists(dirPath))
    {
      for (auto&& file : fs::directory_iterator(dirPath)) {
        if (fs::is_regular_file(file)) {
          if (hasPath)
            files.push_back(file.path().string()); 
          else
            files.push_back(file.path().filename().string());
        }
      }
    }

    return files;
  }

  /**************************************************************************/
  /*!
  @brief Scans a folder, given a path and extracts all the files paths
         with a given extension into a string vector.
  @param dirPath The directory path.
  @param extension The extension which to extract.
  @return The string vector, containing all the files paths.
  */
  /**************************************************************************/
  FileSystem::PathList FileSystem::DirectoryListFiles(const Path & dirPath, const std::string & extension, bool hasPath)
  {
    FileSystem::PathList files;

    if (Exists(dirPath))
    {
      for (auto&& file : fs::directory_iterator(dirPath)) {
        if (file.path().extension().string() != extension)
          continue;

        if (fs::is_regular_file(file)) {
          if (hasPath)
            files.push_back(file.path().string());
          else
            files.push_back(file.path().filename().string());
        }
      }
    }

    return files;
  }

}