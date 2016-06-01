#include "FileSystem.h"

FileSystem::FileSystem() {
  this->rootDir = new Dir("/");
  rootDir->setParent(rootDir);
  this->currentDir = this->rootDir;
}

FileSystem::~FileSystem() {
  
}

Dir* FileSystem::getCurrentDir() {
  return this->currentDir;
}

void FileSystem::route(const string cmd) {
  
}

const vector<string> FileSystem::parse(const string path) {
  stringstream ss(path);
  vector<string> elems;
  string item;
  while (getline(ss, item, '/')) {
    elems.push_back(item);
  }
  if (*(path.rbegin()) == '/') {
    elems.push_back("");
  }
  return elems;
}

File* FileSystem::getElementByPath(const string path) {
  auto elems = FileSystem::parse(path);
  Dir* p = NULL;
  File* elem = NULL;
  int i = 0;
  
  if (elems[0] == "") { // Absolute path
    p = this->rootDir;
    i = 1;
  } else { // Relative path
    p = this->currentDir;
    i = 0;
  }
  
  for (i; i < elems.size(); i++) {
    if (elems[i] == "..") {
      p = p->parent();
      continue;
    } else {
      elem = p->getElementByName(elems[i]);
      if (elem != NULL) {
        if (elem->isDir()) {
          if (i == elems.size() - 1) {
            return elem;
          } else {
            p = static_cast<Dir*>(elem);
            continue;
          }
        } else {
          if (i == elems.size() - 1) {
            return elem;
          } else {
            printf("%s is a file !!!\n", elems[i].c_str());
            break;
          }
        }
      } else {
        if (i == elems.size() - 1) {
          return p;
        } else {
          printf("Can't find directory %s!!!\n", elems[i].c_str());
          break;
        }
      }
    }
  }
  
  return NULL;
}

void FileSystem::switchToDir(const string path) {
  
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
