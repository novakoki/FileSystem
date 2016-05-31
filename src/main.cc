#include <iostream>
#include "FileSystem.h"

int main () {
  auto fs = new FileSystem();
  string cmd = "";
  cout<<"ziqi@Ziqi:~$ ";
  while(getline(cin, cmd)) {
    fs->route(cmd);
    cout<<"ziqi@Ziqi:"<<fs->getCurrentDir()<<"$ ";
  }
  return 0;
}
