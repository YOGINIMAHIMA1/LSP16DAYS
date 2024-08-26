#include <iostream>
using namespace std;
class Student{
    private:
    string name;
    public:
    int rollno;
    char grade;
     
     Student(string name ,int rollno, char grade){
        this->name=name;
        this->rollno=rollno;
        this->grade=grade;
     }
     void printAll(){
        cout<<name<<" "<<rollno<<" "<<grade<<endl;
     }
};
int main(){
  Student S("kiara",121,'A');
   S.printAll();
  

  
}