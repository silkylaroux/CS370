//Include the necessary header file.
#include <stdio.h>
/* Skeleton Code 
     * Define a char pointer, filename, that holds a file name. Initialize filename as "textfile.txt"
     * Check if argument count (argc) is more than one. 
     * If it is more than one, then argv[1] is the file name passed as a parameter. 
     * Use argv[1] as the filename now, by assigning argv[1] to filename
     * Declare a 1D Character array, 'sentence', to hold the entire content read from 
     * the file and a 2D Character array, 'commands' to hold the commands read from the file.
     * Assume there is only one line in the file, with multiple UNIX commands.
     * Each command is separated by a comma.
     * Open the file using fopen function
     * Check if the file opened successfully. 
     * If not print the statement "File opening has failed. Ending program." and then exit the program.
     * Get the line present in the file using the fgets function.
     * Close the file using the fclose function.
     */

    /* Keep a variable x and y, both initialized to 0, where y points to the position in 'commands' 2-D array in the xth row.
     * Remember, every row in the 'commands' array holds a different command.
     * In a for loop, use an iterating variable, and go to every character in the 'sentence' array, and check if it is a comma.
     * If it is not a comma, set the yth position in the xth row of commands array with the sentence[i] value, and increment the value of y.
     * Else if it is comma, or it is the EOF character (\0), set the yth position in the xth row of commands array to '\0', 
     * increment the x value to point the next row, as the command in the present row is now complete. Set y to 0.
     * End of for loop.
     *//* Keep a variable x and y, both initialized to 0, where y points to the position in 'commands' 2-D array in the xth row.
     * Remember, every row in the 'commands' array holds a different command.
     * In a for loop, use an iterating variable, and go to every character in the 'sentence' array, and check if it is a comma.
     * If it is not a comma, set the yth position in the xth row of commands array with the sentence[i] value, and increment the value of y.
     * Else if it is comma, or it is the EOF character (\0), set the yth position in the xth row of commands array to '\0', 
     * increment the x value to point the next row, as the command in the present row is now complete. Set y to 0.
     * End of for loop.
     */
int main(int argc, char **argv) 
{
    char *filename = "textfile.txt";
    if(argc > 1){
        filename = argv[1];
    }

    char *sentence;
    char **commands;

    FILE *given_file;
    given_file = fopen(filename,"r");

    if(given_file == NULL){
        printf(%s\n, "File opening has failed. Ending program.");
        return 1;
    }else{
        sentence = fgets(given_file);
        fclose(given_file);

        int x = 0;
        int y = 0;

        for(int i = 0; i < sizeof(sentence); i++){
            if(sentence[i] == ',' || sentence[i] == '\0'){
                commands[x][y] = '\0';
                x++;
                y = 0;
            }else{
                commands[x][y] = sentence[i];
                y++;
            }
        }
        for(int i = 0; i < x+1; i++){
            int fam_check = fork();
            if(fam_check == 0){

            }else{

            }
        }

    }
     
     /* Create a for loop that iterates through the commands array. 0 to x+1 should be the range of the for loop as x has the count of commands except the last command.
     * Inside the for loop, fork a child process.
     * 1. If inside the Parent process display the following text
     *      "ParentProgram: forked process with ID *child_process_id*."
     *      "ParentProgram: waiting for process [*child_process_id*]."
     *    Then create an integer variable waitstatus_v, to get the status of the child process.
     *    Use wait() to wait for the child process to complete the execution. Pass address of waitstatus_v as parameter to wait()
     *    Get the exit status of the child process using WEXITSTATUS() with the input parameter as waitstatus_v.
     *    Print the following statement
     *      "ParentProgram: Child process *child_process_id* returned *status*"
     * 2. If inside the Child process, invoke the command executor program, Executor.c using the function execlp int the following way:
     *      execlp("./Executor","Executor",passcommand,NULL);
     * 3. If forking has failed, Print the following statement and exit the program.
     *      "ParentProgram: Child Process Creation failed. Exiting."
     * End for loop.
     * Print the statement "ParentProgram: Process Complete."
     */
    
	
    
    
    //Write your code here
    
}

