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
int main(int argc, char **argv)
{
    char* sentence = malloc(sizeof(*sentence));             // MUST FREE
   
    char *filename = "textfile.txt";
    if (argc > 1) {
        filename = argv[1];                                   // Reads given file if
    }     
    //char sentence[100];
    int pip_int = atoi(argv[2]);
    FILE *given_file;
    given_file = fopen(filename, "r");
//printf("here");
    if (given_file == NULL) {                               // Checks if there is a file
        printf("%s\n", "File opening has failed. Ending program.");
        exit(0);
    } else {
    sentence = fgets(sentence, 100, given_file);          // Reads file line into sentence
    fclose(given_file);   
    }
    
    write(pip_int,sentence,strlen(sentence));
    free(sentence);
    return 1;


}