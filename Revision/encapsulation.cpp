// wrapping up data member and member function into a single unit called class. but these
// data member cannot be accessible outside the class only accessible by those  member function 
//present inside class

#include <iostream>
using namespace std;
 class student{
    private:
    int rollno;
    char grade;
    string subject;
    public:
    void accessRollno(int Rno){
      this-> rollno=Rno;
    }
    void accessGrade(char Grd){
        this->grade=Grd;
    }
    void accessSubject(string Sub){
        this->subject=Sub;
    }
    void access(){
        cout<<rollno<<" "<<grade<<" "<<subject<<endl;
    }
 };
 int main(){
    student S;
   S.accessRollno(123);
   S.accessGrade('A');
   S.accessSubject("english");
   S.access();
 }