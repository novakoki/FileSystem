#include "Dir.h"

Dir::Dir(const string name) {
  this->name = name;
  this->size = 0;
  this->type = 1;
  this->firstChild = NULL;
  this->lastChild = NULL;
  this->parentNode = NULL;
}

void Dir::setParent(Dir* parentNode) {
  this->parentNode = parentNode;
}

Dir* Dir::parent() {
  return this->parentNode;
}

File* Dir::first() {
  return this->firstChild;
}

File* Dir::last() {
  return this->lastChild;
}

File* Dir::getElementByName(const string name) {
  for (auto p = firstChild; p != NULL; p = p->next()) {
    if (p->getName() == name) {
      return p;
    }
  }
  return NULL;
}

void Dir::appendChild(File* pNewNode) {
  pNewNode->setNext(NULL);
  if (pNewNode->isDir()) {
    static_cast<Dir*>(pNewNode)->parentNode = this;
  }
  if (this->lastChild != NULL) {
    this->lastChild->setNext(pNewNode);
  } else {
    this->firstChild = pNewNode;
  }
  this->lastChild = pNewNode;
  this->size++;
}

void Dir::forEach(function<void(File*)> callback) {
  for (auto p = firstChild; p != NULL; p = p->next()) {
    callback(p);
  }
}

Dir* Dir::cloneNode() {
  Dir* newNode = new Dir(this->name);
  this->forEach([&newNode](File* p) -> void {
    newNode->appendChild(p->cloneNode());
  });
  return newNode;
}
