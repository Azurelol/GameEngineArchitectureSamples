/*!****************************************************************************\
@file   FileSystem_File.cpp
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
  @brief  Creates a file.
  @param  The new file, in its path.
  @return A boolean determining the success of the operation.
  \**************************************************************************/
  bool FileSystem::FileCreate(const Path & filePath)
  {
    std::ofstream newFile(filePath);
    if (newFile) {
      newFile.close();
      return true;
    }

    return false;
  }

  /*!************************************************************************\
  @brief  Returns the size of the file, in bytes.
  @param  The file path.
  @return The size of the file in bytes, an unsigned integer.
  \**************************************************************************/
  unsigned FileSystem::FileSize(const Path & filePath)
  {
    if (Exists(filePath))
      return static_cast<unsigned>(fs::file_size(filePath));

    return 0;
  }

  /*!************************************************************************\
  @brief  Renames a file.
  @param  The file path.
  @param  The new filename.
  @return A boolean determining the success of the operation.
  \**************************************************************************/
  bool FileSystem::FileRename(const Path & filePath, Path newFileName)
  {
    fs::path newPath = fs::path(filePath).parent_path() / newFileName;
    if (Exists(filePath)) {
      fs::rename(filePath, newPath);
      return true;
    }

    return false;
  }


  /*!************************************************************************\
  @brief  Extracts a file's contents into a single string.
  @param  filePath The file path.
  @param  output The string to write to.
  @return The success of the operation.
  @note   This operation is particularly useful for deserializing data.
  \**************************************************************************/
  bool FileSystem::FileRead(const Path & filePath, std::string & output)
  {
    std::ifstream inputFile(filePath);
    if (inputFile)
    {
      std::string content((std::istreambuf_iterator<char>(inputFile)), (std::istreambuf_iterator<char>()));
      output = content;
      return true;
    }
    return false;
  }

  /*!************************************************************************\
  @brief Writes the specified string to a file.
  @param filePath The new file, in its path.
  @param input The string to write to the file.
  @param append Whether to append the string or not. If not appending, will overwrite.
  @return A boolean determining the success of the operation.
  \**************************************************************************/
  bool FileSystem::FileWrite(const Path & filePath, const std::string& input, bool append)
  {
    std::ofstream file(filePath);

    if (file)
    {
      if (!append)
        file.clear();

      file << input;
      file.close();
      return true;
    }
    return false;
  }

  /*!************************************************************************\
  @brief  get a file without its extension or preceeding path
  @param  filePath The file path.
  @return A new string without the extension or path
  \**************************************************************************/
  FileSystem::Path FileSystem::FileNoExtension(const Path& filePath)
  {
    return fs::path(filePath).stem().string();
  }

  /*!************************************************************************\
  @brief  Returns a file's extension.
  @param  filePath The file path.
  @return A new string containing the extension's name.
  \**************************************************************************/
  FileSystem::Path FileSystem::FileExtension(const Path& filePath)
  {
    return fs::path(filePath).extension().string();
  }

  /*!************************************************************************\
  @brief  Returns whether a file has the given extension.
  @param  filePath The file path.
  @param  extension The extension of the file.
  @return Whether the file has the specified extension or not.
  \**************************************************************************/
  bool FileSystem::FileHasExtension(const Path& filePath, const std::string& extension)
  {
    if (FileExtension(filePath) == extension)
      return true;
    return false;
  }


  /*!************************************************************************\
  @brief  Returns a file name without its path.
  @param  filePath The file path.
  @return A new string without the path
  \**************************************************************************/
  FileSystem::Path FileSystem::FileNoPath(const Path& filePath)
  {
    return fs::path(filePath).filename().string();
  }




}