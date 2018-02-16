// Damian Armijo
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
    printf("%s: Command: %s\n",argv[0],argv[1]);        // Prints out the file, and it's command
    int checker = system(argv[1]);                      // Gets command return status
    printf("Executor Process ID: %d\n",getpid());
    return(checker);                                    // Returns the value returned by the system()
                                                        // Call
}