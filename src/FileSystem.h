#pragma once
#include <vector>
#include <sstream>
#include "File.h"
#include "Dir.h"

class FileSystem {
  private:
    Dir* rootDir;
    Dir* currentDir;
    string helpMessage;

  public:
    FileSystem();
    ~FileSystem();

    void route(const string&);
    static const vector<string> split(const string&, const char&);
    static const vector<string> parse(const string&);
    Dir* getCurrentDir();
    Dir* getRootDir();
    File* getElementByPath(const vector<string>&);
    Dir* getParentDirByPath(const vector<string>&, function<void(const string&, Dir*)>);

    void switchToDir(const string&);
    void listDir(const string&);
    Dir* makeDir(const string&);

    File* makeFile(const string&);
    void editFile(const string&);
    void readFile(const string&);

    File* copy(const string&, const string&);
    void remove(const string&);
    File* move(const string&, const string&);
};
