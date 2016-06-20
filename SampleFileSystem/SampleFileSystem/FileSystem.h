/*!****************************************************************************\
@file   FileSystem.h
@author Christian Sagel
@date   5/29/2016
@brief  Provides facilities for performing operations on file systems and their 
        components, such as paths, regular files, and directories. 

\******************************************************************************/
#pragma once

// Libraries: Ideally you would have these on a precompiled header
//            or on a separate header your cpps would include.
#include <filesystem> 
#include <fstream>
#include <string>
#include <vector>
#include <ctime> // time_t

namespace Systems {

  class FileSystem
  {
  public:

    using Path = std::string;
    using PathList = std::vector<Path>;

    /* Shell */
    static bool Execute(std::string command);
    static bool Execute(const std::string& command, const std::vector<std::string>& arguments);

    /* File Dialog */
    static std::string  FileOpenDialog(const Path& defaultPath, const Path& filters);
    static std::string  FileSaveDialog(const Path& defaultPath, const Path& filters);

    /* Path Operations*/
    static bool         Exists(const Path& path);
    static std::time_t  LastModified(const Path& path);
    static bool         Delete(const Path& path);
    static void         Correct(Path&);
    static Path         RelativePath(const Path& path, const Path& pathRelativeTo);

    /* File Operations */
    static bool         FileCreate(const Path& filePath);
    static unsigned     FileSize(const Path& filePath);
    static bool         FileRename(const Path& filePath, Path newFileName);
    static bool         FileRead(const Path& filePath, std::string& output);
    static bool         FileWrite(const Path& filePath, const std::string& input, bool append = false);
    static Path         FileNoExtension(const Path& filePath);
    static Path         FileExtension(const Path& filePath);
    static bool         FileHasExtension(const Path& filePath, const std::string& extension);
    static Path         FileNoPath(const Path& filePath);

    /* Folder Operations */
    static Path         DirectoryCurrent();
    static bool         DirectoryCreate(const Path& dirPath);
    static PathList     DirectoryListFiles(const Path& dirPath, bool hasPath = true);
    static PathList     DirectoryListFiles(const Path& dirPath, const std::string& extension, bool hasPath = true);
    static bool         DirectoryListDirs(const Path& dirPath, std::vector<Path>& dirs);
    static bool         DirectoryContainsFile(const Path& dirPath, const Path& fileName, Path& foundPath);
    static unsigned     DirectoryCountFiles(const Path& dirPath);
    static unsigned     DirectoryCountDirs(const Path& dirPath);
  };

}