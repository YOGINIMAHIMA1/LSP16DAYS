#include <iostream>
using namespace std;
class Student{
    private:
    string name;
    public:
    char grade;
    int rollno;
    Student(string name, char grade, int rollno){
        this->name=name;
        this->grade=grade;
        this->rollno=rollno;
    }
    Student(Student &obj){
        this ->name="riddhi";
        this->grade='b';
        this->rollno=obj.rollno;
    }
    void printAll(){
    cout<<name<<" "<<grade<<" "<<rollno<<endl;
    }
};
int main(){
    Student S("teena",'A',1212);
    Student S1(S);
    S1.printAll();
}