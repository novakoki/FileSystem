#pragma once
#include <string>
#include <iostream>
#include <cstdio>
using namespace std;

class File {
  private:
    string content;
  protected:
    string name;
    int size;
    int type;
    File* nextSibling;

  public:
    File();
    File(const string, const string);
    ~File();
    string getName();
    void setName(const string);
    int getSize();
    string getContent();
    File* next();
    File* cloneNode();
    void setNext(File*);
    bool isDir();
};