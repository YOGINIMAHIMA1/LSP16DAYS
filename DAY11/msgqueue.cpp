#include <iostream>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>

struct msg_buffer {
    long msg_type;
    char msg_text[100];
};

int main() {
    key_t key;
    int msgid;
    struct msg_buffer message;

    // Generate a unique key
    key = ftok("progfile", 65);

    // Create a message queue
    msgid = msgget(key, 0666 | IPC_CREAT);
    message.msg_type = 1;

    if (fork() == 0) {  // Child process
        strcpy(message.msg_text, "Hello from child!");
        msgsnd(msgid, &message, sizeof(message), 0);
        std::cout << "Child sent message: " << message.msg_text << std::endl;
    } else {  // Parent process
        msgrcv(msgid, &message, sizeof(message), 1, 0);
        std::cout << "Parent received message: " << message.msg_text << std::endl;
        msgctl(msgid, IPC_RMID, NULL);  // Destroy the message queue
    }

    return 0;
}
