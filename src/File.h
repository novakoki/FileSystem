#include <string>
using namespace std;

class File {
  private:
    string name;
    int size;
    string content;
    
  public:
    string getName ();
    void setName (const string name);
    int getSize ();
    string getContent ();
};
