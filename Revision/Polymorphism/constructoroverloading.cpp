#include <iostream>
using namespace std;
class Student{
    public:
    int age;
    char grade;
    string name;
    Student(){
      cout<<" non-paramterized constructer called"<<endl;
    }
    Student(int age, char grade, string name){
      this->age=age;
      this->grade=grade;
      this->name=name;
    }
};
int main(){
    Student S;
    Student S1(21,'A',"kavya");
    cout<<S1.age<<" "<<S1.grade<<" "<<S1.name<<endl;

}