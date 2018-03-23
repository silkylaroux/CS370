// Damian Armijo
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/ipc.h> 
#include <sys/stat.h> 
#include <sys/sem.h>
#include <fcntl.h>
#include <sys/mman.h>
#define O_RDONLY         00
#define O_WRONLY         01
#define O_RDWR           02

int main(int argc, char **argv)
{
    printf("%s: Command: %s\n",argv[0],argv[1]);        // Prints out the file, and it's command
    //int checker = system(argv[1]);                      // Gets command return status
    printf("Executor Process ID: %d\n",getpid());

    int size = 256;
    int shm_fd;
    void *ptr;
    
    shm_fd = shm_open(argv[1],O_CREAT | O_RDWR,0666);
    ptr = mmap(0,size,PROT_READ, MAP_SHARED, shm_fd,0);
    sprintf(ptr,"%d",getpid());
    printf("here\n");

    ptr++;
    shm_unlink(argv[1]);
    exit(0);                                   // Returns the value returned by the system()
                                                        // Call
}