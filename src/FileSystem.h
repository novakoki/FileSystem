#pragma once
#include "File.h"
#include "Dir.h"

class FileSystem {
  private:
    Dir* rootDir;
    Dir* currentDir;

  public:
    FileSystem();
    ~FileSystem();

    File* getFileByName(const string);
    Dir* getDirByName(const string);
    void route(const string);
    Dir* getCurrentDir();

    void switchToDir(const string);
    void listDir(const string);
    void copyDir(const string, const string);
    void removeDir(const string);
    void makeDir(const string);

    void makeFile(const string);
    void removeFile(const string);
    void editFile(const string);
    void readFile(const string);
    void copyFile(const string, const string);

};
