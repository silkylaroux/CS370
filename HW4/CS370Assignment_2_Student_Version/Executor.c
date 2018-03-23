// Damian Armijo
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
/*
* The Executor program takes in as the second argument the command to be run by the system.
* It runs the command, and then sends the execution value to the pipe.
*/
int main(int argc, char **argv)
{
    int checker = system(argv[1]);                          // Runs system command and gets return status
    printf("\n%s: Given Command is: \'%s\' with process id %d\n",argv[0],argv[1],getpid());        // Prints out the file, and it's command

    int size = 256;
    int shm_fd;                                             // Creates a pointer for reading into
    void *ptr;                                              // the pipe.
    
    shm_fd = shm_open(argv[1],O_CREAT | O_RDWR,0666);   
    ptr = mmap(0,size,PROT_READ, MAP_SHARED, shm_fd,0);     // Maps the execution to the pipe
    sprintf(ptr,"%d",checker);

    ptr++;
    shm_unlink(argv[1]);                                    // Unlinks the pipe

    exit(0);                                                // Exits
}