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

string Dir::getAbsolutePath() {
  string path = "";
  if (this == this->parent()) {
    return "/";
  }
  for (auto p = this; p != p->parent(); p = p->parent()) {
    path = "/"+p->getName()+path;
  }
  return path;
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

File* Dir::appendChild(File* pNewNode) {
  pNewNode->setNext(NULL);
  pNewNode->setPrev(this->lastChild);
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
  return pNewNode;
}

void Dir::removeChild(File* pNode) {
  if (pNode == firstChild) {
    if (pNode == lastChild) {
      firstChild = NULL;
      lastChild = NULL;
    } else {
      pNode->next()->setPrev(pNode->prev());
      firstChild = pNode->next();
    }
  } else if (pNode == lastChild) {
    pNode->prev()->setNext(pNode->next());
    lastChild = pNode->prev();
  } else {
    pNode->prev()->setNext(pNode->next());
    pNode->next()->setPrev(pNode->prev());
  }
  this->size--;
  if (pNode->isDir()) {
    Dir* dir = static_cast<Dir*>(pNode);
    dir->forEach([&dir](File* p) -> void {
      dir->removeChild(p);
    });
  }
  
  delete pNode;
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

bool Dir::contains(Dir* pNode) {
  while (pNode != pNode->parent()) {
    if (pNode == this) {
      return true;
    }
    pNode = pNode->parent();
  }
  return false;
}
