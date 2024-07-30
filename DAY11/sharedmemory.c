#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <fcntl.h>
#include <errno.h>

#define SHM_SIZE 1024
#define SEM_NAME "/shm_sem"

int main() {
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, SHM_SIZE, 0666|IPC_CREAT);
    if (shmid == -1) {
        perror("shmget failed");
        exit(EXIT_FAILURE);
    }
    char *str = (char*) shmat(shmid, NULL, 0);
    if (str == (char*) -1) {
        perror("shmat failed");
        exit(EXIT_FAILURE);
    }

    sem_t *sem = sem_open(SEM_NAME, O_CREAT, 0644, 1);
    if (sem == SEM_FAILED) {
        perror("sem_open failed");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid > 0) {  // Parent process
        sem_wait(sem);
        strcpy(str, "Hello from parent");
        sem_post(sem);

        wait(NULL);

        printf("Data in shared memory: %s\n", str);
        if (shmdt(str) == -1) {
            perror("shmdt failed");
            exit(EXIT_FAILURE);
        }
        if (shmctl(shmid, IPC_RMID, NULL) == -1) {
            perror("shmctl failed");
            exit(EXIT_FAILURE);
        }
        if (sem_close(sem) == -1) {
            perror("sem_close failed");
            exit(EXIT_FAILURE);
        }
        if (sem_unlink(SEM_NAME) == -1) {
            perror("sem_unlink failed");
            exit(EXIT_FAILURE);
        }
    } else {  // Child process
        sem_wait(sem);
        printf("Data read from shared memory: %s\n", str);
        sem_post(sem);
        if (shmdt(str) == -1) {
            perror("shmdt failed");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
