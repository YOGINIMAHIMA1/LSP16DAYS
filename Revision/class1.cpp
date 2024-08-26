#include <iostream>
using namespace std;
class Student{
    private:
    string name;
    int rollno;
     string subject;
     public:
     void print(string sub){
        cout<<sub<<" ";
     }
};
class Teacher{
    private:
    double salary;
    public:
    string name;
    string dept;

    string subject;
     double PrintAll(double sal){
         sal=salary;
        return sal;
     }

};
int main(){
    Student s;
    //s.subject="english";// show err main has not direct access to use subject data member
    s.print("English");
    Teacher t;
     t.name="Sheena Bajaj";
     cout<<t.name<<endl;
  
   cout<<t.PrintAll(1234.567);
}