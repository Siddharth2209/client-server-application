#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h> 
#include <sys/mman.h>
//#include

#define MAX_TEXT 512
#define MAX_CLIENTS 10
#define MAX_NAME_LENGTH 256
#define CONNECT_CHANNEL_SIZE 1024
#define COMM_CHANNEL_SIZE 1024
#define Max_requests 100

typedef struct shared_memory {
    int requested;
    int responded;
    int request;
    char operation;
    double number;
    double operand1;
    double operand2;
    double result;
} SharedMemory;

SharedMemory* shared_memory1;
SharedMemory* shared_memory2; 

// void handler(int sig) {
//     if (sig == SIGINT) {
//         shmdt(shared_memory);
//         exit(0);
//     }
// }

int main() {
    const int SIZE = 4096;
    void *shm_ptr;
    char temp[100];
    char buffer[100];
    char buffer2[100];

    //signal(SIGINT, handler);

    int shmid,shmid2;
    key_t connectkey = 1111;
    //Asking for shared memory
    shmid = shmget(connectkey, sizeof(SharedMemory), 0666 | IPC_CREAT);
    
    if(shmid<0) {
        perror("Error Creating the shared memory...\n");
    }
    //attaching to the shared memory 
    shm_ptr = shmat(shmid,NULL,0);

    if(shm_ptr==(char*)-1) {
        perror("Error Attaching The Shared Memory...\n");
    }

    strcpy(temp, shm_ptr);
    printf("Client is running....\n");
    sleep(2);
    printf(" Enter the name of the client...\n");
    read(0,buffer,100);
    strcpy(temp,buffer);//data copied from buffer to shared memory
    sleep(5);
    printf("Key received : %s\n",(char*)(temp));
    sleep(2);


    //************** CREATING COMMUNICATION CHANNEL *******************
    key_t commkey = 1122;
    char temp2[100];
    shmid2= shmget(commkey, CONNECT_CHANNEL_SIZE, 0666 | IPC_CREAT);
    printf("Communication Channel Shared Memory Created....\n");
    if(shmid2<0) {
        perror("Error Creating the shared memory...\n");
    }
    shared_memory2 = shmat(shmid2, NULL,0);           //Process attached at shared memory segment 
    // if(shared_memory2 == (char*)-1) {
    //     perror("Error in attaching...\n");
    // }
    sleep(4);

    printf("Enter a request: \n1. Arithmetic\n2. Find whether even or odd\n3. Is prime?\n4. Is it negative\n5. Unregister\n6. Exit\n");
    read(0, temp2, 100);
            char num1[1024];
            char num2[1024];
            char op[10];
    switch(temp2[0]){
        case '1':
            printf("Enter first number: ");
            scanf("%lf\n", &shared_memory2->operand1);
            printf("Enter second number: ");
            scanf("%lf\n", &shared_memory2->operand2);
            printf("Enter the operation:\n1. Addition\n2. Substraction\n3. Multiplication\n4.Division\n");
            scanf("%c\n", &shared_memory2->operation);            
            break;
        case '2':
            printf("Enter 1 number: ");
            scanf("%lf\n", &shared_memory2->number);
            break;
        case '3':
            printf("Enter 1 number: ");
            scanf("%lf\n", &shared_memory2->number);
            break;
        case '4':
            printf("Enter 1 number: ");
            scanf("%lf\n", &shared_memory2->number);
            break;
        case '5':
            shared_memory2->request= 1;
            break;
        case '6':
            printf("Exiting...\n");
            exit(0);
            break;
        default:
            printf("Error: Invalid choice\n");
            break;
    }
    
    // printf("Waiting for server connections...\n");
    // strcpy(temp2, shm_ptr2);            // Saving the head of the shared memory
    // printf("%s\n", temp2);
    // memset(temp2, ' ', strlen((char*)(temp2))*sizeof(char));
    // printf("%s\n", temp2);
    // read(0,buffer2,100);
    // strcpy(temp2,buffer2);              //data copied from buffer to shared memory

    //************** CREATING COMMUNICATION CHANNEL *******************

    shmdt(shm_ptr);
    return 0;
}