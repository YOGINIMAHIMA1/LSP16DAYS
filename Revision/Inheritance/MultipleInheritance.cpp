#include <iostream>
using namespace std;
class Person{
    public:
    string name;
    char grade;
    int rollno;
};
class Student {
public:
int age;
};
class GrandStudent : public Student , public Person{
    public:
void printAll(){
    cout<<name<<" "<<grade<<" "<<rollno<<" "<<age<<endl;
}
};
int main(){

GrandStudent G;
G.name="ruhi";
G.grade='A';
G.rollno=12;
G.age=21;
G.printAll();
}