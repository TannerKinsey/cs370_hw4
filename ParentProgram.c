//Include the necessary header file.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(int argc, char **argv)
{

    /* Skeleton Code
     * Define a char pointer, filename, that holds a file name. Initialize filename as "textfile.txt"
     * Check if argument count (argc) is more than one. If it is more than one, then argv[1] is the file name passed as a parameter. Use argv[1] as the filename now, by assigning argv[1] to filename
     *
     *
     * Declare a 1D Character array, 'sentence', to hold the entire content read from the file and a 2D Character array, 'commands' to hold the commands read from the file.
     * Assume there is only one line in the file, with multiple UNIX commands. Each command is separated by a comma.
     * Open the file using fopen function
     * Check if the file opened successfully. If not print the statement "File opening has failed. Ending program." and then exit the program.
     * Get the line present in the file using the fgets function.
     * Close the file using the fclose function.
     *
     * Keep a variable x and y, both initialized to 0, where y points to the position in 'commands' 2-D array in the xth row. Remember, every row in the 'commands' array holds a different command.
     * In a for loop, use an iterating variable, and go to every character in the 'sentence' array, and check if it is a comma.
     * If it is not a comma, set the yth position in the xth row of commands array with the sentence[i] value, and increment the value of y.
     * Else if it is comma, or it is the EOF character (\0), set the yth position in the xth row of commands array to '\0', increment the x value to point the next row, as the command in the present row is now complete. Set y to 0.
     * End of for loop.
     *
     * Create a for loop that iterates through the commands array. 0 to x+1 should be the range of the for loop as x has the count of commands except the last command.
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
	//seting the default to textfile.txt
  char* filename = "textfile.txt";
	//checking if there is a file to read from
  if(argc > 1){
      filename = argv[1];
      printf("FILENAME: %s\n",filename);
  }
	//creating a pointer and setting it equal to the begining of the input file
  FILE *file = fopen(filename, "r");
	//case for a null file... exit program with error message
  if(file == NULL){
      printf("File opening has failed. Ending program.\n");
      exit(0);
  }
	//creating two variables one to keep track of how many characters are in the file
	//the other to use as a null char indecator
  int charCounter = 1;
	int charElement;
  while((charElement = fgetc(file))){
	//there are no more valid characters in the file... leave the loop
      if(charElement == EOF){
          break;
      }
      charCounter++;
  }
	//declare an array with the size = to the number of chars in the file
  char sentence [charCounter];
	//declare a 2d array with the size = to the number of chars in the file squared
	char commands[charCounter][charCounter];
	//rewind sets the pointer back to the begining of the file
	rewind(file);
	//fgets(where to store info, how many chars to store, where to get the info from)
	fgets(sentence, charCounter, file);
    fclose(file);//close the file im done with it
	//declaring 2 variables to navigate the 2d array
	int x = 0;
	int y = 0;
	//loop through contents of sentence, deliniate on commas, and start filling in the next row down until you hit the next comma
	for(int i = 0; i < charCounter; i++){
		if(sentence[i] != ','){
			commands[x][y] = sentence[i];
			y++;
		}
		else{
			x++;
			y = 0;//must set y back to 0 to start filling in the next row in column 0
		}
	}
	//go through all rows and fork child processes at each command line command
	for(int i = 0; i <= x; i++){
		pid_t pid;
		pid = fork();
		if(pid > 0){//parent process

      
			printf("PARENT PROGRAM: forked process with ID %d.\n",pid);
			printf("PARENT PROGRAM: waiting for process [%d].\n",pid);
            int waitstatus_v = pid;
            wait(&waitstatus_v);
            WEXITSTATUS(waitstatus_v);
            printf("PARENT PROGRAM: Child process %d returned %d.\n",pid,waitstatus_v);
		}
    if(pid == 0){//child process
      if((execlp("./Executor","Executor", commands[i], NULL)) == -1){
        printf("PARENT PROGRAM: Child Process Creation failed. Exiting.\n");
          break;
      }
    }
    if(pid < 0){
      printf("ERROR WITH FORK PROCESS");
        exit(0);
    }
  }
  printf("PARENT PROGRAM: Process Complete.\n");

  return 0;
}
