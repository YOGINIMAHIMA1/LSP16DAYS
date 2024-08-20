#include <iostream>
#include <string>
using namespace std;

class Name{
  public:
    string firstName;
    string lastName;
    void PrintName(){
        cout<<firstName<<" "<<lastName<<endl;
    }
};
int main(){
    Name N;
    N.firstName="xoxo";
    N.lastName="Khan";
 N.PrintName();
}

