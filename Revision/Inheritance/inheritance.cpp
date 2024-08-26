#include <iostream>
using namespace std;
class Teacher{
     public:
    string name;
    string dept;
    int marks;

    Teacher(string name, string dept, int marks){
      this->name=name;
      this->dept=dept;
      this->marks=marks;
        cout<<"Parent constructor"<<endl;
    }
};
class  student: public Teacher{
    
    public:
    int rollno;
    char grade;
    student(string name,string dept, int marks, int rollno, char grade): Teacher( name,  dept,  marks){
        this->rollno=rollno;
        this->grade=grade;
    }
    void printAll(){
        cout<<name<<" "<<dept<<" "<<marks<<" "<<rollno<<" "<<grade<<endl;

    }
    
};
int main(){
   student S("kanya","cs",89,12,'A');// pehle parent constructor call hoyge then child constructor jab object create hoga
   Teacher T();
   S.printAll();
}