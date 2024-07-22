#include <iostream>
#include <csignal>
#include <unistd.h>
using namespace std;
//signal Handler Function
void signalHandler(int signum){
    cout<<"Whatever interrupt signal("<<signum<<") recieved .\n";
    exit(signum);
}
int main(){
    signal(SIGINT,signalHandler);
    signal(SIGSEGV,signalHandler);
    while(true)
    {
    cout<<"Running .... Press Ctrl +c to exist \n";
    sleep(1);
    }

}