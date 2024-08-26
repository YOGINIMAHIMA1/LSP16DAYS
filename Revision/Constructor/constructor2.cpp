#include <iostream>
using namespace std;
class Student{
    private:
    int rollno;
    public:
    string name;
    char grade;
    string subject;


    Student(){
        cout<<"Default Constructor"<<endl;
    }
    //Paramterized constructor
    Student(int rno, string n ,char grd, string sub){
      rollno=rno, name=n, grd=grade, subject=sub;
    }
     void printAll(){
        
        cout<<rollno<<" "<<name<<" "<<grade<<" "<<subject<<endl;
     }
};
int main(){
    Student S;
    Student S1(11,"Kylie",'A',"ENGLISH");
    S1.printAll();

}