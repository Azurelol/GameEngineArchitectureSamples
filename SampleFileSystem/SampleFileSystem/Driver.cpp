#include "FileSystem.h"

// Logging, ho!
#include <iostream>
#define Trace(message) std::cout << message << std::endl;

void PrintSize(const std::string& filePath);
void PrintLastModified(const std::string& filePath);
void PrintExists(const std::string& filePath);

int main(void) {

  Trace("FileSystem Library demonstration \n");
  std::string filePath;
  filePath = "Driver.cpp"; // Feel free to change it!

  // FileSystem::Exists ------------------------------------------------------/  
  Trace("1. Let's find if the file '" + filePath + "' exists in the current directory!");  
  PrintExists(filePath);
  // FileSystem::LastModified ------------------------------------------------------/
  Trace("2. Let's find when the last time '" + filePath + "' was modified!");
  PrintLastModified(filePath);
  // FileSystem::FileSize ------------------------------------------------------/
  Trace("3. Let's find the size of '" + filePath + "' in bytes.");
  PrintSize(filePath);

  // FileSystem::FileCreate ------------------------------------------------------/
  filePath = "NewFile.txt";
  Trace("4. Now let's create a file of our own. Creating '" + filePath + "'");
  Systems::FileSystem::FileCreate(filePath);
  Trace("Let's check if it was really created...");
  PrintLastModified(filePath);
  // FileSystem::FileWrite ------------------------------------------------------/
  Trace("5. Let's write a string to it. Before we do that, let's check its size first...'");
  PrintSize(filePath);
  Trace("Writing a string to it...");
  std::string thesisStatement = "The Duc is assassinated and there is panic in the streets \
    of Defiance Bay. Lady Webb may be the only person who can reestablish order. I need to \
    make my way to Hadret House and tell her what happened.";
  Systems::FileSystem::FileWrite(filePath, thesisStatement);
  Trace("Let's now check its size again...");
  PrintSize(filePath);
  // FileSystem::FileRename ------------------------------------------------------/
  std::string newFilePath = "TotallyNewFile.txt";
  Trace("6. Let's rename that file. Renaming '" + filePath + "' to '" + newFilePath + "'");
  Systems::FileSystem::FileRename(filePath, newFilePath);
  // FileSystem::DirectoryListFiles --------------------------------------------/
  Trace("7. Let's check if it was truly renamed. Let's get a list of the files without their paths) in the current directory");
  Trace(" (Note: The second argument of the method is whether the relative paths of the files should be included or not)");
  auto currentDir = Systems::FileSystem::DirectoryCurrent();
  auto filesInDir = Systems::FileSystem::DirectoryListFiles(currentDir, false);
  for (auto& file : filesInDir)
    Trace(" - '" + file + "' ");
  // FileSystem::FileRead ------------------------------------------------------/
  Trace("8. Let's now read the contents from the renamed file '" + newFilePath + "' ...");
  std::string contents;
  Systems::FileSystem::FileRead(newFilePath, contents);
  Trace(contents);


  return 0;
}


void PrintSize(const std::string & filePath)
{
  auto size = Systems::FileSystem::FileSize(filePath);
  Trace("'" + filePath + "' is of size '" + std::to_string(size) + "' bytes");
}

void PrintLastModified(const std::string & filePath)
{
  auto timeModified = Systems::FileSystem::LastModified(filePath);
  Trace("'" + filePath + "' was last modified at " + std::asctime(std::localtime(&timeModified)));
}

void PrintExists(const std::string & filePath)
{
  if (Systems::FileSystem::Exists(filePath)) {
    Trace("'" + filePath + "' was found!");
  }
  else {
    Trace("'" + filePath + "' was not found!");
  }
}
