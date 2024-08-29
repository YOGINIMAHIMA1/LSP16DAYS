#include <iostream>

using namespace std;
class Person{
    public:
    string name;
    char grade;
   
};
class Student:public Person{
    public:
    int age;
     
};
class Student1:public Person{
    

};
int main(){
    Student S;
    S.name="Drishti";
    S.grade='A';
    S.age=12;
    Student1 S1;
    S1.name="Rahul";
    S1.grade='B';
    cout<<S.name<<" "<<S.age<<endl;
    cout<<S1.name<<" "<<S1.grade<<endl;

}
