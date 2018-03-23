// Damian Armijo
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
/*
 * This is the ParentProgram, it takes in 1 input, which is the name of the file
 * that contains the commands. It creates a pipe, and using this pipe it calls FileOpener
 * which gets the commands. After closing the pipe it takes the given commands
 * and runs them with Executor.
*/
int main(int argc, char **argv) {

  if(argc<2){                                             // Checks if correct number of arguments
    printf("%s: Needs more arguments!\n",argv[0]);
    exit(1);
  }

  int pip[2];
  if(pipe(pip)==-1){                                      // Tries to create the pipe
    printf("%s\n","Pipe failed!");
    return 1;
  }
  char txt[100] = "";                                     // txt holds the commands
  int pid = fork();                                       // Forks process

  if(pid >0){                                             // Parent process
      printf("%s%d.\n", "ParentProgram: Forked process with ID ", pid);
      printf("%s%d].\n", "ParentProgram: Waiting for process [", pid);
      int waitstatus_v;
      wait(&waitstatus_v);

      close(pip[1]);                                      // Closes writing
      read(pip[0],txt,sizeof(txt));                       // Reads into the pipe
      close(pip[0]);
      printf("Sentence is %s\n",txt);
      printf("ParentProgram: Child process %d returned: %d\n",pid,waitstatus_v);

  }
  else if(pid ==0){                                       // Child process
    char FD[100];
    sprintf(FD,"%d",pip[1]);                              // Writes into the pipe
    execlp("./FileOpener", "FileOpener",argv[1] ,FD,NULL);

  } else {
      printf("%s\n", "ParentProgram: Child Process Creation failed. Exiting.");
  }
    
  char** commands = (char**) calloc(5, sizeof(char*));    //***MUST FREE***
  for (int i = 0; i < 5; i++ ){   
    commands[i] = (char*) calloc(1, sizeof(char));        // dynamic allocation for commands
  }

    int x = 0;
    int y = 0;

    for (int i = 0; i < strlen(txt); i++) {               // Processes contents of the pipe and
      if (txt[i] == ','||'\0') {                          // Puts it into commands array.
        commands[x][y] = '\0';
        x++;
        y = 0;

      } else {
        commands[x][y] = txt[i];
        y++;
      }
    }

    for (int i = 0; i < x + 1; i++) {
      pid_t id_check = fork(); 
      int returnID;
      const char *v_write_mem = "Shared_mem";

      if (id_check == 0) {                                // Child process
        execlp("./Executor","Executor",commands[i],v_write_mem,NULL);

      } else if(id_check > 0) {                           // Parent process
        printf("%s%d.\n", "ParentProgram: Forked process with ID ", id_check);
        printf("%s%d].\n", "ParentProgram: Waiting for process [", id_check);

        int shm_fd, size = 256;                           // Creates a size buffer of 256
        void *ptr;
        shm_fd = shm_open(v_write_mem,O_CREAT | O_RDWR,0666);
        ftruncate(shm_fd,size);                           // Truncates to 256
        ptr = mmap(0,size,PROT_READ, MAP_SHARED, shm_fd,0); // maps the value to the pointer for the pipe
        printf("ParentProgram: FD for shared memory for Executor is %d\n", shm_fd);
        
        int waitstatus_v;
        wait(&waitstatus_v);
        sscanf(ptr,"%d",&returnID);                       // Reads into the pipe pointer
        shm_unlink(v_write_mem);                          // Unlinks
        printf("ParentProgram: Child process %d returned %d.\n",id_check,returnID);

      } else {
        printf("%s\n", "ParentProgram: Child Process Creation failed. Exiting.");
      }
    }

    for ( int i = 0; i < 5; i++ ){
      free(commands[i]);                                  //***FREEING***
    }
    free(commands);

    printf("%s\n", "ParentProgram: Process Complete.");
  }
  
