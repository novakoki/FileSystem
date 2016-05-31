#include "Dir.h"

Dir::Dir(const string name) {
  this->name = name;
  this->size = 0;
  this->type = 1;
  this->firstChild = NULL;
  this->lastChild = NULL;
}

void Dir::appendChild(File* pNewNode) {
  pNewNode->setNext(NULL);
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
