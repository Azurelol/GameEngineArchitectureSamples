/*!****************************************************************************\
@file   FileSystem.cpp
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
  @brief  Looks for a file or directory in a given path.
  @param  The path of the file or directory
  @return Whether the file or directory was found or not.
  \**************************************************************************/
  bool FileSystem::Exists(const Path & path)
  {
    if (fs::exists(path))
      return true;
    return false;
  } 

  /*!************************************************************************\
  @brief  Finds out when a file was last modified.
  @param  The file path.
  @return The last time the file was modified, an std::time_t object.
  \**************************************************************************/
  std::time_t FileSystem::LastModified(const Path & path)
  {
    fs::path pathObj = path;
    fs::file_time_type time;
    if (Exists(path))
      time = fs::last_write_time(pathObj);
    return std::time_t(decltype(time)::clock::to_time_t(time));
  }

  /*!************************************************************************\
  @brief  Delets a file or directory (and all its contained files)
  @param  The file path.
  @param  The new filename.
  @return A boolean determining the success of the operation.
  \**************************************************************************/
  bool FileSystem::Delete(const Path & path)
  {
    if (Exists(path)) {
      fs::remove_all(path);
      return true;
    }

    return false;
  }

  /*!************************************************************************\
  @brief  Fixes the current path in the string to be compatible with
          file dialogs.
  @param  path The file path.
  \**************************************************************************/
  void FileSystem::Correct(Path & path)
  {
    std::replace(path.begin(), path.end(), '/', '\\');
  }

  /*!************************************************************************\
  @brief  Translates an absolute path to a relative path, given the path
          to be translated as well as the path it should be relative to.
  @param  path The file path.
  @param  pathRelativeTo The file path relative to.
  @return A relative path.
  \**************************************************************************/
  FileSystem::Path FileSystem::RelativePath(const Path & path, const Path & pathRelativeTo)
  {
    return Path();
  }




}