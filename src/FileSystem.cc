#include "FileSystem.h"

FileSystem::FileSystem() {
  this->rootDir = new Dir("/");
  rootDir->setParent(rootDir);
  this->currentDir = this->rootDir;
  helpMessage = "usage: <command> [path1] [path2]\n\nThe most commonly used commands are:\ncat     Display content of some file\ncd      Switch to some directory\ncp      Copy and paste\necho    Write content to some file\nexit    Back to terminal\nhelp    Display this guide\nls      List directory's content\nmkdir   Create a directory\nmv      Move/Rename a file or directory\nrm      Remove a file or directory\ntouch   Create a file\n\n\"help <command>\" show specifical guides\n";
}

FileSystem::~FileSystem() {
  
}

Dir* FileSystem::getRootDir() {
  return this->rootDir;
}

Dir* FileSystem::getCurrentDir() {
  return this->currentDir;
}

void FileSystem::route(const string& cmd) {
  if (cmd.empty()) {
    return;
  }
  
  auto elems = split(cmd, ' ');
  int length = elems.size();
  auto op = elems[0];
  
  if (op == "cd") {
    if (length > 2) {
      cout<<"Invalid arguments!!!"<<endl;
    } else if (length == 2) {
      switchToDir(elems[1]);
    }
  } else if (op == "ls") {
    if (length > 2) {
      cout<<"Invalid arguments!!!"<<endl;
    } else if (length == 1) {
      listDir("");
    } else {
      listDir(elems[1]);
    }
  } else if (op == "touch") {
    if (length != 2) {
      cout<<"Invalid arguments!!!"<<endl;
    } else {
      makeFile(elems[1]);
    }
  } else if (op == "mkdir") {
    if (length != 2) {
      cout<<"Invalid arguments!!!"<<endl;
    } else {
      makeDir(elems[1]);
    }
  } else if (op == "rm") {
    if (length != 2) {
      cout<<"Invalid arguments!!!"<<endl;
    } else {
      remove(elems[1]);
    }
  } else if (op == "cp") {
    if (length != 3) {
      cout<<"Invalid arguments!!!"<<endl;
    } else {
      copy(elems[1], elems[2]);
    }
  } else if (op == "mv") {
    if (length != 3) {
      cout<<"Invalid arguments!!!"<<endl;
    } else {
      move(elems[1], elems[2]);
    }
  } else if (op == "cat") {
    if (length != 2) {
      cout<<"Invalid arguments!!!"<<endl;
    } else {
      readFile(elems[1]);
    }
  } else if (op == "echo") {
    if (length != 3) {
      cout<<"Invalid arguments!!!"<<endl;
    } else {
      writeFile(elems[1], elems[2]);
    }
  } else if (op == "exit") {
    exit(0);
  } else if (op == "help") {
    if (length == 1) {
      cout<<helpMessage<<endl;
    } else if (length == 2) {
      
    } else {
      cout<<"Invalid arguments!!!"<<endl;
    }
  } else {
    cout<<"Invalid command!!!"<<endl;
  }
  
  return;
}

const vector<string> FileSystem::split(const string& s, const char& delimiter) {
  stringstream ss(s);
  vector<string> elems;
  string item;
  while (getline(ss, item, delimiter)) {
    elems.push_back(item);
  }

  return elems;
}

const vector<string> FileSystem::parse(const string& path) {
  return split(path, '/');
}

File* FileSystem::getElementByPath(const vector<string>& elems) {
  Dir* p = NULL;
  File* elem = NULL;
  int i = 0;

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

Dir* FileSystem::getParentDirByPath(const vector<string>& path, function<void(const string&, Dir*)> callback) {
  vector<string> tmp(path);
  Dir* parentDir;
  auto name= *tmp.rbegin();
  tmp.pop_back();
  
  if (name == "") {
    printf("Dir or file name should not be empty!!!\n");
  } else {
    parentDir = static_cast<Dir*>(getElementByPath(tmp));
    if (parentDir != NULL) {
      callback(name, parentDir);
    } else {
      printf("Path is not valid!!!\n");
    }
  }
  
  return parentDir;
}

void FileSystem::switchToDir(const string& path) {
  auto elems = parse(path);
  auto elem = getElementByPath(elems);
  if (elem != NULL) {
    if (elem->isDir()) {
      this->currentDir = static_cast<Dir*>(elem);
    } else {
      printf("%s is a file!!!\n", (*elems.rbegin()).c_str());
    }
  } else {
    printf("Path is not valid!!! %s\n", path.c_str());
  }
}

void FileSystem::listDir(const string& path) {
  Dir* dir = getCurrentDir();
  if (!path.empty()) {
    auto elem = getElementByPath(parse(path));
    if (elem != NULL) {
      dir = static_cast<Dir*>(elem);
    }
  }
  if (dir->getSize() != 0) {
    dir->forEach([](File* p) -> void {
      if (p->isDir()) {
        printf("\033[01;34m%s\033[0m  ", p->getName().c_str());
      } else {
        printf("%s  ", p->getName().c_str());
      }
    });
    printf("\n");
  }
}

Dir* FileSystem::makeDir(const string& path) {
  if (path.empty()) {
    printf("Dir name should not be empty\n");
    return NULL;
  }
  
  Dir* dir = NULL;

  getParentDirByPath(parse(path), [&dir](const string& dirName, Dir* parentDir) -> void {
    if (parentDir->getElementByName(dirName) == NULL) {
      dir = new Dir(dirName);
      parentDir->appendChild(dir);
    } else {
      printf("%s exists!!!\n", dirName.c_str());
    }
  });
  
  return dir;
}

File* FileSystem::makeFile(const string& path) {
  if (path.empty()) {
    printf("File name should not be empty\n");
    return NULL;
  }
  
  File* file = NULL;
  
  getParentDirByPath(parse(path), [&file](const string& fileName, Dir* parentDir) -> void {
    if (parentDir->getElementByName(fileName) == NULL) {
      file = new File(fileName, "");
      parentDir->appendChild(file);
    } else {
      printf("%s exists!!!\n", fileName.c_str());
    }
  });
  
  return file;
}

File* FileSystem::copy(const string& srcPath, const string& dstPath) {
  if (srcPath.empty() || dstPath.empty()) {
    printf("Dir or file name should not be empty\n");
    return NULL;
  }
  
  File* node = NULL;
  auto src = getElementByPath(parse(srcPath));
  if (src != NULL) {
    getParentDirByPath(parse(dstPath), [&node, src, srcPath, dstPath](const string& dstName, Dir* parentDir) -> void {
      if (parentDir->getElementByName(dstName) == NULL) {
        if (src->isDir() && static_cast<Dir*>(src)->contains(parentDir)) {
          printf("%s is child of %s\n", dstPath.c_str(), srcPath.c_str());
        } else {
          node = src->cloneNode();
          node->setName(dstName);
          parentDir->appendChild(node);
        }
      } else {
        printf("%s exists!!!\n", dstName.c_str());
      }
    });
  } else {
    printf("%s not exists!!!\n", srcPath.c_str());
  }
  
  return node;
}

void FileSystem::remove(const string& path) {
  if (path.empty()) {
    printf("Dir or file name should not be empty\n");
    return;
  }
  
  getParentDirByPath(parse(path), [](const string& name, Dir* parentDir) -> void {
    auto elem = parentDir->getElementByName(name);
    if (elem != NULL) {
      parentDir->removeChild(elem);
    } else {
      printf("%s not exists!!!\n", name.c_str());
    }
  });
}

File* FileSystem::move(const string& srcPath, const string& dstPath) {
  auto dst = copy(srcPath, dstPath);
  remove(srcPath);
  return dst;
}

void FileSystem::readFile(const string& filePath) {
  auto file = getElementByPath(parse(filePath));
  if (file == NULL) {
    printf("%s not exists!!!\n", filePath.c_str());
  } else if (file->isDir()) {
    printf("%s is a directory!!!\n", filePath.c_str());
  } else {
    cout<<file->getContent()<<endl;
  }
}

void FileSystem::writeFile(const string& filePath, const string& content) {
  auto file = getElementByPath(parse(filePath));
  if (file == NULL) {
    printf("%s not exists!!!\n", filePath.c_str());
  } else if (file->isDir()) {
    printf("%s is a directory!!!\n", filePath.c_str());
  } else {
    file->setContent(content);
  }
}
