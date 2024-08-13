#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdbool.h>
#include <signal.h>
#include <unistd.h>

typedef struct shared_memory {
    bool requested;
    bool responded;
    char operation;
    double operand1;
    double operand2;
    double Result;
} SharedMemory;

SharedMemory* shared_memory;

void handler(int sig) {
    if (sig == SIGINT) {
        shmdt(shared_memory);
        exit(0);
    }
}

int main() {
    key_t key;
    int shmid;

    signal(SIGINT, handler);

    key = ftok("server", 65); // unique key for shared memory
    shmid = shmget(key, sizeof(SharedMemory), 0666 | IPC_CREAT); // create shared memory with permissions

    if (shmid == -1) {
        perror("Error creating shared memory");
        exit(1);
    }

    shared_memory = shmat(shmid, NULL, 0); // attach to shared memory

    while (1) {
        if (shared_memory->requested && !shared_memory->responded) { // check if client has requested an operation
            double operand1 = shared_memory->operand1;
            double operand2 = shared_memory->operand2;
            double Result;

            // perform the requested operation
            switch (shared_memory->operation) {
                case '+':
                    Result = operand1 + operand2;
                    break;
                case '-':
                    Result = operand1 - operand2;
                    break;
                case '*':
                    Result = operand1 * operand2;
                    break;
                case '/':
                    Result = operand1 / operand2;
                    break;
                default:
                    Result = 0.0;
                    break;
            }

            shared_memory->Result = Result;

            // notify client that operation has been performed
            shared_memory->requested = false;
            shared_memory->responded = true;

            printf("Sent Result: %lf\n", shared_memory->Result);
        }
    }

    shmdt(shared_memory); // detach from shared memory

    // remove the shared memory
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("Error removing shared memory");
        exit(1);
    }

    return 0;
}