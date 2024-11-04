#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>


int main(){

    int pid =fork();

    if(pid ==0)
    {
        printf("CHILD: My PID is %d and my parent's PID is %d\n", getpid(), getppid());
    }
    else
    {
        printf("PARENT: My PID is %d and my parent's PID is %d\n", getpid(), getppid());
    }
    return 0;


}