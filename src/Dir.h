#pragma once
#include <functional>
#include "File.h"

class Dir:public File {
  private:
    File* firstChild;
    File* lastChild;
    Dir* parentNode;

  public:
    Dir(const string);
    ~Dir();
    void appendChild(File*);
    void setParent(Dir*);
    Dir* cloneNode();
    Dir* parent();
    File* first();
    File* last();
    void forEach(function<void(File*)>);
    File* getElementByName(const string);
};
