#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
void sort_strings(char * arr[],int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            if(strcmp(arr[j],arr[j+1])>0)
            {
                char *temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

int main(int argc,char* argv[])
{
    int status;
    
    int n = argc-1;
    char* arr[n];
    for(int i=0;i<n;i++)
    {
        arr[i] = argv[i+1];
    }

    int pid = fork();
    if(pid == 0)
    {
        sort_strings(arr,n);
        printf("child:\n");
        for(int i=0;i<n;i++)
        {
            printf("%s ",arr[i]);
        }
        printf("\n");
        // exit(0);
    }
    else{
        wait(&status);
        printf("parent:\n");
        for(int i=0;i<n;i++)
        {
            printf("%s ",arr[i]);
        }
        printf("\n");
        if(WIFEXITED(status))
        {
            printf("Child exited with staus %d\n",WEXITSTATUS(status));
        }
    }
    return 0;


}