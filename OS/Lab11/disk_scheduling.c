#include<stdio.h>
#include<limits.h>
#include<stdlib.h>
void sort(int arr[],int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            if(arr[j] > arr[j+1])
            {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}
void sstf(int req[],int n, int head)
{
    printf("SSTF:");
    int visited[n];
    int total=0;
    for(int i=0;i<n;i++)
    {
        visited[i]=0;
    }

    for(int i=0;i<n;i++)
    {
        int mini = INT_MAX;
        int ind = -1;
        for(int j=0;j<n;j++)
        {
            if(visited[j] == 0 && abs(head - req[j]) < mini)
            {
                mini = abs(head - req[j]);
                ind = j;
            }
        }
        total += abs(head - req[ind]);
        printf("%d -> ",req[ind]);
        head = req[ind];
        visited[ind] = 1;
    }

    printf("\n");
    printf("total seek time: %d\n",total);
}

void scan(int req[],int n, int head,int disk_size)
{
    sort(req,n);
    int total =0;
    int start = INT_MAX;
    for(int i=0;i<n;i++)
    {
        if(req[i] >= head)
        {
            start = i;
            break;
        }
    }

    for(int i=start;i<n;i++)
    {
        printf("%d ",req[i]);
        total += abs(head - req[i]);
        head = req[i];
    }
    total += abs(head - disk_size + 1);
    printf("%d ",disk_size-1);
    head = disk_size-1;

    for(int i = start-1;i>=0;i--)
    {
        total += abs(head - req[i]);
        printf("%d ",req[i]);
        head = req[i];
    }

    printf("Total sek time: %d",total);
}

void cscan(int req[],int n,int head,int disk_size)
{
    sort(req,n);
    int start;
    int total=0;
    for(int i=0;i<n;i++)
    {
        if(req[i] >= head)
        {
            start = i;
            break;
        }
    }

    for(int i=start+1;i<n;i++)
    {
        total += abs(head - req[i]);
        printf("%d ",req[i]);
        head = req[i];
    }

    printf("%d ",disk_size-1);
    total += abs(head - disk_size +1);
    total += disk_size-1;
    head =0;
    for(int i=0;i<start;i++)
    {
        total += abs(head -req[i]);
        printf("%d ",req[i]);
        head = req[i];
    }
    printf("\nTotal seek time: %d",total);
}

void look(int req[],int n,int head)
{
    sort(req,n);
    int start;
    int total=0;
    for(int i=0;i<n;i++)
    {
        if(req[i] >= head)
        {
            start=i;
            break;
        }
    }

    for(int i=start;i<n;i++)
    {
        total += abs(req[i]-head);
        printf("%d ",req[i]);
        head = req[i];
    }
    for(int i=start-1;i>=0;i--)
    {
        total += abs(req[i]-head);
        printf("%d ",req[i]);
        head = req[i];
    }

    printf("\nTotal seek time: %d\n",total);
}
void clook(int req[],int n,int head)
{
    sort(req,n);
    int start;
    int total=0;
    for(int i=0;i<n;i++)
    {
        if(req[i] >= head)
        {
            start = i;
            break;
        }
    }

    for(int i=start;i<n;i++)
    {
        total += abs(req[i] - head);
        printf("%d ",req[i]);
        head = req[i];
    }
    total += abs(head - req[0]);
    head = req[0];
    printf("%d ",req[0]);
    for(int i=0;i<start;i++)
    {
        total += abs(req[i] - head);
        printf("%d ",req[i]);
        head = req[i];
    }
    printf("\nTotal seek time: %d\n",total);
}
void FCFS(int req[],int n,int head)
{
    int total=0;

    for(int i=0;i<n;i++)
    {
        printf("%d -> ",req[i]);
        total += abs(head - req[i]);
        head = req[i];
    }
    printf("\nTotal seek time: %d\n",total);
}
int main()
{
    int opt,n,head,disk_size;
    printf("Enter n:");
    scanf("%d",&n);

    int req[n];
    printf("Enter requests: ");
    for(int i=0;i<n;i++)
    {
        scanf("%d", &req[i]);
    }

    printf("Enter head:" );
    scanf("%d",&head);

    while(1)
    {
        printf("1)sstf\n2)scan\n3)csan\n4)look\n5)clook\n6)FCFS");
        scanf("%d",&opt);
        switch(opt)
        {
            case 1:
                sstf(req,n,head);
                break;
            case 2:
                printf("Enter disk size:");
                scanf("%d", &disk_size);
                scan(req,n,head,disk_size);
                break;

            case 3:
                printf("Enter disk size:");
                scanf("%d", &disk_size);
                cscan(req,n,head,disk_size);
                break;
            case 4:
                look(req,n,head);
                break;
            case 5:
                clook(req,n,head);
                break;
            case 6:
                FCFS(req,n,head);
                break;
        }
    }
    
}