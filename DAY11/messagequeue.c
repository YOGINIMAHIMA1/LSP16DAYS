#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#define MAX_TEXT 100

struct msg_buffer {
    long msg_type;
    char msg_text[MAX_TEXT];
};

int main() {
    key_t key = ftok("progfile", 65);
    int msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget failed");
        exit(EXIT_FAILURE);
    }

    struct msg_buffer message;
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid > 0) {  // Parent process
        message.msg_type = 1;
        strcpy(message.msg_text, "Hello from parent!");
        if (msgsnd(msgid, &message, sizeof(message.msg_text), 0) == -1) {
            perror("msgsnd failed");
            exit(EXIT_FAILURE);
        }

        wait(NULL);

        if (msgrcv(msgid, &message, sizeof(message.msg_text), 2, 0) == -1) {
            perror("msgrcv failed");
            exit(EXIT_FAILURE);
        }
        printf("Parent received: %s\n", message.msg_text);

        if (msgctl(msgid, IPC_RMID, NULL) == -1) {
            perror("msgctl failed");
            exit(EXIT_FAILURE);
        }
    } else {  // Child process
        if (msgrcv(msgid, &message, sizeof(message.msg_text), 1, 0) == -1) {
            perror("msgrcv failed");
            exit(EXIT_FAILURE);
        }
        printf("Child received: %s\n", message.msg_text);

        message.msg_type = 2;
        strcpy(message.msg_text, "Hello from child!");
        if (msgsnd(msgid, &message, sizeof(message.msg_text), 0) == -1) {
            perror("msgsnd failed");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
