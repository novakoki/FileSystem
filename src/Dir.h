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
    Dir* cloneNode();
    void forEach(function<void(File*)>);
};
