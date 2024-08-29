#include <iostream>
using namespace std;
class A{
   public:
   void replace(){
    cout<<"child replaced"<<endl;
   }
};
class B: public A{
    public:
    void replace(){
        cout<<"Parent replaced"<<endl;
    }

};
int main(){
    A a;
    a.replace();
}