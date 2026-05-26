#include "kernel/types.h" //Has typedefs for common types in xv6
#include "user/user.h"

//Main
int main(void)
{
    int childPid = fork();
    if(childPid == 0) //This is the child
    {   
        int* arr = (int*)malloc(sizeof(int)*100); //Allocate an array to make size bigger
        printf("Child info\n");
        procinfo(); //Print process info
        free(arr);  //Deallocate array
    }
    else //If this is the parent, wait for the child
    {
        wait(&childPid);
        printf("Parent info\n");
        procinfo();
    }
}