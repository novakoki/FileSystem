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
    File* previousSibling;

  public:
    File();
    File(const string, const string);
    ~File();
    string getName();
    void setName(const string);
    int getSize();
    string getContent();
    void setContent(const string&);
    File* next();
    File* prev();
    virtual File* cloneNode();
    void setNext(File*);
    void setPrev(File*);
    bool isDir();
};
