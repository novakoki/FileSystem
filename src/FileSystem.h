#pragma once
#include <vector>
#include <sstream>
#include "File.h"
#include "Dir.h"

class FileSystem {
  private:
    Dir* rootDir;
    Dir* currentDir;

  public:
    FileSystem();
    ~FileSystem();

    void route(const string&);
    static const vector<string> parse(const string&);
    Dir* getCurrentDir();
    Dir* getRootDir();
    File* getElementByPath(const vector<string>&);

    void switchToDir(const string&);
    void listDir(const string&);
    Dir* copyDir(const string&, const string&);
    Dir* removeDir(const string&);
    Dir* makeDir(const string&);
    Dir* makeDir(const string&, Dir*);

    void makeFile(const string&);
    void removeFile(const string&);
    void editFile(const string&);
    void readFile(const string&);
    void copyFile(const string&, const string&);

};
