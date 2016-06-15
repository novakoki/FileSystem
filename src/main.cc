#include "FileSystem.h"

int main () {
  system("clear");
  auto fs = new FileSystem();
  cout<<fs->helpMessage<<endl;
  string cmd = "";
  cout<<"ziqi@Ziqi:"<<fs->getCurrentDir()->getAbsolutePath()<<"$ ";
  while(getline(cin, cmd)) {
    fs->route(cmd);
    cout<<"ziqi@Ziqi:"<<fs->getCurrentDir()->getAbsolutePath()<<"$ ";
  }
  return 0;
}
