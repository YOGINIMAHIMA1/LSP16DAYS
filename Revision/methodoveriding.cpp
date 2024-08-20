#include <iostream>
using namespace std;

class Animal{
    public:
    void sound(){};
} ;
class Dog :public Animal{
    public:
    void sound(){
        cout<<"Dog bark"<<endl;
    }
};
class Cat:public Animal{
    public:
    void sound(){
        cout<<"cat meow";
    }
};
int main(){
    Dog D;
    D.sound();
    Cat C;
    C.sound();
}