#include <iostream>
using namespace std;
class Student{
    public:
    void fun( int task){
        
        cout<<task<<endl;
    }
    void fun(string task){
        
         cout<<task<<endl;
    }
};

int main(){
    Student S;
    S.fun(21);
    S.fun("Mahima");
}