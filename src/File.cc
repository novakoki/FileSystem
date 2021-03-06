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

void File::setPrev(File* pPrevNode) {
  this->previousSibling = pPrevNode;
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

void File::setContent(const string& content) {
  this->content = content;
}

File* File::next() {
  return this->nextSibling;
}

File* File::prev() {
  return this->previousSibling;
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
