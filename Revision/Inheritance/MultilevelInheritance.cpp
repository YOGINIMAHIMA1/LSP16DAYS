#include <iostream>
using namespace std;
class Person{
public:
string name;
char grade;
int rollno;
};
class Student: public  Person{
    public:
    int age;
};
class GrandStudent :public Student {
    public:
    int marks;
   
    void printAll(){
        cout<<name<<" "<<grade<<" "<<rollno<<" "<<age<<" "<<marks<<endl;
    }

};
int main(){
   GrandStudent G;
   G.name="garima";
   G.grade= 'A';
   G.rollno=12;
   G.age= 21;
  G.marks=89;
   G.printAll();
}