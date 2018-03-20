//Include the necessary header file.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(int argc, char **argv)
{
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
