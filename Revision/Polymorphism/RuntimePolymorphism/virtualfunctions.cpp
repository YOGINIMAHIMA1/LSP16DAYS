#include <iostream>
using namespace std;
class Student{
  public:
  void show(){
    cout<<"show me";
  }

};
class Student1:public virtual Student{
    public:

};
class Student2:public  virtual Student{
    public:

};
class Student3 :public Student1 ,public Student2{
    public:
};
int main(){
    Student3 S;
    S.show();

}