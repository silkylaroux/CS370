#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
/*
 * This is the FileOpener, it takes in 2 arguments. The first is the filename,
 * the second is the pipe to be written into. It tries to open the file, and 
 * if successful it will write to the pipe sent in. 
 */
int main(int argc, char **argv)
{
    char* sentence = malloc(sizeof(*sentence));             //***MUST FREE***
    char *filename = "textfile.txt";
    if (argc > 1) {
        filename = argv[1];                                 // Reads given file if
    }

    int pip_int = atoi(argv[2]);
    FILE *given_file;
    given_file = fopen(filename, "r");

    if (given_file == NULL) {                               // Checks if there is a file
        printf("%s\n", "File opening has failed. Ending program.");
        exit(0);
    } else {
        sentence = fgets(sentence, 100, given_file);        // Reads file line into sentence
        fclose(given_file);   
    }

    write(pip_int,sentence,strlen(sentence));               // Writing the sentence into the pipe
    unlink(argv[2]);
    free(sentence);                                         // Freeing sentence
    return 1;


}