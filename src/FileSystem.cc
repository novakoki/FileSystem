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

void FileSystem::route(const string& cmd) {
  
}

const vector<string> FileSystem::parse(const string& path) {
  stringstream ss(path);
  vector<string> elems;
  string item;
  while (getline(ss, item, '/')) {
    elems.push_back(item);
  }
  // if (*(path.rbegin()) == '/') {
  //   elems.push_back("");
  // }
  return elems;
}

File* FileSystem::getElementByPath(const vector<string>& elems) {
  Dir* p = NULL;
  File* elem = NULL;
  int i = 0;
  
  // Problem here
  if (elems.empty()) {
    return this->currentDir;
  }
  
  if (elems[0] == "") { // Absolute path
    p = this->rootDir;
    i = 1;
  } else { // Relative path
    p = this->currentDir;
    i = 0;
  }
  
  for (; i < elems.size(); i++) {
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
        return NULL;
      }
    }
  }
  
  return p;
}

void FileSystem::switchToDir(const string& path) {
  auto elems = FileSystem::parse(path);
  auto elem = getElementByPath(elems);
  if (elem != NULL) {
    if (elem->isDir()) {
      this->currentDir = static_cast<Dir*>(elem);
    } else {
      printf("%s is a file!!!\n", (*elems.rbegin()).c_str());
    }
  } else {
    printf("Path is not valid!!!\n");
  }
}

Dir* FileSystem::makeDir(const string& path) {
  auto elems = FileSystem::parse(path);
  vector<string> tmp(elems);
  auto dirName= *tmp.rbegin();
  tmp.pop_back();
  if (dirName == "") {
    dirName = *tmp.rbegin();
    tmp.pop_back();
  }
  
  auto parentDir = static_cast<Dir*>(getElementByPath(tmp));
  if (parentDir != NULL) {
    return makeDir(dirName, parentDir);
  } else {
    printf("Path is not valid!!!\n");
    return NULL;
  }
}

Dir* FileSystem::makeDir(const string& dirName, Dir* parentDir) {
  if (parentDir->getElementByName(dirName) == NULL) {
    Dir* newDir = new Dir(dirName);
    parentDir->appendChild(newDir);
    return newDir;
  } else {
    printf("%s exists!!!\n", dirName.c_str());
    return NULL;
  }
}

void FileSystem::makeFile(const string& name) {
  File* newFile = new File(name, "");
  this->currentDir->appendChild(newFile);
} 

void FileSystem::listDir(const string& name) {
  this->currentDir->forEach([](File* p) -> void {
    if (p->isDir()) {
      printf("\033[01;34m%s\033[0m  ", p->getName().c_str());
    } else {
      printf("%s  ", p->getName().c_str());
    }
  });
  printf("\n");
}
