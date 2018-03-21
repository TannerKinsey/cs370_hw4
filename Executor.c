// Include the necessary header files here.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(int argc, char **argv)
{
    /*In this program you have to print the name of the program, along with the given command and the process Id
     *Execute the command using system() function
     *Return the status of execution of the system() to the parent program
     */
    
    // Type your code here
    printf("Executor: Given Command is: '%s' with process id %d.\n",argv[1],getpid());
    return system(argv[1]);
}
