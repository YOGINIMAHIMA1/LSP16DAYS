#include <iostream>
#include <unistd.h>

using namespace std;
int main(){
    pid_t pid;
    pid =fork();
    if(pid==0){
       cout<<pid<<" "<<getpid()<<" "<<getppid()<<endl;
    }
    else{
        cout<<pid<<" "<<getpid()<<" "<<getppid()<<endl;
    }
}