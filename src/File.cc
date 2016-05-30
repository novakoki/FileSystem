#include "File.h"

string File::getName () {
  return this->name;
}

void File::setName (const string name) {
  this->name = name;
}

int File::getSize () {
  return this->size;
}

string File::getContent () {
  return this->content;
}
