#include <iostream>
using namespace std;
class Student{
   public:
   void operatoroverloading(int a){
   int b;
    b=a;
     cout<<a<<" "<<b<<endl;
   }
};
int main(){
    Student S;
    S.operatoroverloading(10);

}