#include  <iostream>
using namespace  std;
class Person{
  public:
  int age;
  char grade;
  string name ;
};
class Student: public virtual Person {
  public:
   string subject;

};
class GrandStudent: public virtual Person{
  public:
  int id;
};

class GrandgrandStudent : public Student, public GrandStudent{


};
int main(){
  GrandgrandStudent G;
  G.subject="english";
  G.id=1;
  G.age=22;
  G.grade='A';
  cout<<G.subject<<" "<<G.id<<" "<<G.age<<" "<<G.grade<<endl;
}