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
    string getAbsolutePath();
    File* appendChild(File*);
    void removeChild(File*);
    void setParent(Dir*);
    virtual Dir* cloneNode();
    bool contains(Dir*);
    Dir* parent();
    File* first();
    File* last();
    void forEach(function<void(File*)>);
    File* getElementByName(const string);
};
