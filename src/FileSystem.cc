#include "FileSystem.h"

FileSystem::FileSystem() {
  this->rootDir = new Dir("/");
  this->currentDir = this->rootDir;
}

Dir* FileSystem::getCurrentDir() {
  return this->currentDir;
}

void FileSystem::route(const string cmd) {
  
}

void FileSystem::makeDir(const string name) {
  File* newDir = new Dir(name);
  this->currentDir->appendChild(newDir);
}

void FileSystem::makeFile(const string name) {
  File* newFile = new File(name, "");
  this->currentDir->appendChild(newFile);
} 

void FileSystem::listDir(const string name) {
  this->currentDir->forEach([](File* p) -> void {
    if (p->isDir()) {
      printf("\033[01;34m%s\033[0m  ", p->getName().c_str());
    } else {
      printf("%s  ", p->getName().c_str());
    }
  });
  printf("\n");
}
