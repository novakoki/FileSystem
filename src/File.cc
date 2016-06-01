#include "File.h"

File::File() {
  
}

File::File(const string name, const string content) {
  this->name = name;
  this->content = content;
  this->size = content.length();
  this->type = 0;
}

void File::setNext(File* pNextNode) {
  this->nextSibling = pNextNode;
}

string File::getName() {
  return this->name;
}

void File::setName(const string name) {
  this->name = name;
}

int File::getSize() {
  return this->size;
}

string File::getContent() {
  return this->content;
}

File* File::next() {
  return this->nextSibling;
}

bool File::isDir() {
  if (this->type == 1) {
    return true;
  }
  return false;
}

File* File::cloneNode() {
  File* newNode = new File(this->name, this->content);
  return newNode;
}

File::~File() {
  
}
