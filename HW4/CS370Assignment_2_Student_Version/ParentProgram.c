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
int main(int argc, char **argv) {
  int pip[2];
    

  if(pipe(pip)==-1){
    printf("%s\n","Pipe failed!");
    return 1;
  }
  char txt[100] = "";
  printf("ParentProgram: Text is \'%s\'\n",txt);
  int pid = fork();

  if(pid >0){
      printf("%s%d.\n", "ParentProgram: Forked process with ID ", pid);
      printf("%s%d].\n", "ParentProgram: Waiting for process [", pid);
      int waitstatus_v;
      wait(&waitstatus_v);

      close(pip[1]);
      read(pip[0],txt,sizeof(txt));
      close(pip[0]);
      printf(" Text is \'%s\'\n",txt);
      printf(" Child process %d returned: %d\n",pid,getpid());

  }
  else if(pid ==0){
    char FD[100];
    sprintf(FD,"%d",pip[1]);
    execlp("./FileOpener", "FileOpener",argv[1] ,FD,NULL);

  } else {
      printf("%s\n", "ParentProgram: Child Process Creation failed. Exiting.");
  }
    

    

  pid_t id_check = fork();                            // Forking process, and getting the id
  
  // char *filename = "textfile.txt";
  // if (argc > 1) {
  //   filename = argv[1];                                   // Reads given file if
  // }                                                       // one is given
  
  char* sentence = malloc(sizeof(*sentence));             // MUST FREE
  char** commands = (char**) calloc(5, sizeof(char*));    // MUST FREE
  for (int i = 0; i < 5; i++ ){   
    commands[i] = (char*) calloc(1, sizeof(char));        // dynamic allocation
  }

  // FILE *given_file;
  // given_file = fopen(filename, "r");

  // if (given_file == NULL) {                               // Checks if there is a file
  //   printf("%s\n", "File opening has failed. Ending program.");
  //   exit(0);

  // } else {
  //   sentence = fgets(sentence, 100, given_file);          // Reads file line into sentence
  //   fclose(given_file);                                   // and closes the file
    //printf("%s\n",txt);
    int x = 0;
    int y = 0;
    //printf("strlprogram: content found is %c\n",txt[3]);
    //int z = strlen(txt);
    //printf("%d:%c\n",z,'c');
    for (int i = 0; i < strlen(txt); i++) {          // Processes contents of sentence and
      if (txt[i] == ',') {    // Puts it into commands array.
        commands[x][y] = '\0';
        x++;
        y = 0;

      } else {
        //printf("%d:%c\n",i,txt[i]);
        commands[x][y] = txt[i];
        y++;
      }
    }
      //printf("%c\n",commands[1][0]);
    int returnID;
    for (int i = 0; i < x + 1; i++) {
      const char *v_write_mem = "Shared_mem";
//printf("%s\n",commands[i]);
      if (id_check == 0) {                                // Child process
        execlp("./Executor","Executor",commands[i],v_write_mem,NULL);
        exit(0);

      } else if(id_check > 0) {                           // Parent process
        printf("%s%d.\n", "ParentProgram: Forked process with ID ", id_check);
        printf("%s%d].\n", "ParentProgram: Waiting for process [", id_check);

        int shm_fd, size = 256;
        void *ptr;
        shm_fd = shm_open(v_write_mem,O_CREAT | O_RDWR,0666);
        ftruncate(shm_fd,size);
        ptr = mmap(0,size,PROT_READ, MAP_SHARED, shm_fd,0);
        printf("Program3: FD for shared memory for Executor is %d\n\n", shm_fd);
        
        int waitstatus_v;
        wait(&waitstatus_v);
        sscanf(ptr,"%d",&returnID);
        shm_unlink(v_write_mem);
        printf("Program3: Child process %d returned.\n\n",id_check);
        printf("program: content found is %d\n",returnID);

      } else {
        printf("%s\n", "ParentProgram: Child Process Creation failed. Exiting.");
      }
    }

    free(sentence);                                       // FREEING semtence
    for ( int i = 0; i < 5; i++ ){
      free(commands[i]);                                  // FREEING commands
    }
    free(commands);

    printf("%s\n", "ParentProgram: Process Complete.");
  }
  
