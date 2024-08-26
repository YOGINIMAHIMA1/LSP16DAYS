#include <iostream>
using namespace std;
class Student{
    private:
    string name;
    public:
    char grade;
    int rollno;
    double *cgpa;
    
     Student(string name, char grade, int rollno , double cgpaptr){
       this->name=name;
       this->grade=grade;
       this->rollno=rollno;
       cgpa= new double;
       *cgpa= cgpaptr;



     }
     ~Student(){
        cout<<"destructor deleted object"<<endl;
        delete cgpa; // agr manually delete kr rahe hai  toh iska matlab memory leak nhi hogi
      
     }
     void printAll(){
        cout<<name<<" "<<grade<<" "<<rollno<<" "<<*cgpa<<endl;
     }


};
int main(){
    Student S("haritha",'A',12,8.90);
    S.printAll();
}