// Damian Armijo
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
int main(int argc, char **argv) {
  
  char *filename = "textfile.txt";
  if (argc > 1) {
    filename = argv[1];                                   // Reads given file if
  }                                                       // one is given
  
  char* sentence = malloc(sizeof(*sentence));             // MUST FREE
  char** commands = (char**) calloc(5, sizeof(char*));    // MUST FREE
  for (int i = 0; i < 5; i++ ){   
    commands[i] = (char*) calloc(1, sizeof(char));        // dynamic allocation
  }

  FILE *given_file;
  given_file = fopen(filename, "r");

  if (given_file == NULL) {                               // Checks if there is a file
    printf("%s\n", "File opening has failed. Ending program.");
    exit(0);

  } else {
    sentence = fgets(sentence, 100, given_file);          // Reads file line into sentence
    fclose(given_file);                                   // and closes the file
    
    int x = 0;
    int y = 0;

    for (int i = 0; i < strlen(sentence); i++) {          // Processes contents of sentence and
      if (sentence[i] == ',' || sentence[i] == '\0') {    // Puts it into commands array.
        commands[x][y] = '\0';
        x++;
        y = 0;

      } else {
        commands[x][y] = sentence[i];
        y++;
      }
    }
    
    for (int i = 0; i < x + 1; i++) {
      pid_t id_check = fork();

      if (id_check == 0) {
        execlp("./Executor","Executor",commands[i],NULL);

      } else if(id_check > 0) {
        printf("%s %d.\n", "ParentProgram: forked process with ID", id_check);
        printf("%s %d]\n", "ParentProgram: waiting for process [", id_check);
        int waitstatus_v;
        wait(&waitstatus_v);

          if (WIFEXITED(waitstatus_v == 1))  {
            printf("ParentProgram: Child process %d returned %d\n", id_check, WEXITSTATUS(waitstatus_v));
          }

      } else {
        printf("%s\n", "ParentProgram: Child Process Creation failed. Exiting.");

      }
    }

    free(sentence);                               // FREEING semtence
    for ( int i = 0; i < 5; i++ ){                // FREEING commands
      free(commands[i]);
    }
    free(commands);

    printf("%s\n", "ParentProgram: Process Complete.");
  }

}
