#include <iostream>
using namespace std;
class Student{
    private:
    string name;
    public :
    char grade;
    double salary;
    //constructor- automatically invoke ho jata hai jab class ka object create hota hai agar hum 
    //custom constructor banate hai toh implicit constructor call nahi hota joh constructor 
    // humne create kiya hai voh call hota hai
    // iska naam same hota hai as class name
    //iska koi return type nahi hota
    // only call once when object created
    //memory allocation happens when constructor is called
    
    Student(){
        cout<<"Non-Parameterized Constructor"<<endl;
    }
    Student(string n,char g, double sal){
          name=n;
          grade=g;
          salary=sal;
    }

    void getInfo(){
     cout<<name<<" "<<grade<<" "<<salary<<endl;
    }

};
int main(){
    Student S;
  Student S1("kylie",'A',20000);
  S1.getInfo();
  
}