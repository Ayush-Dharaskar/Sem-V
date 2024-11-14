#include<stdio.h>
#include<limits.h>

void lru(int arr[],int n,int m)
{
    int frames[m],time[m];
    int counter=0,faults=0;

    for(int i=0;i<m;i++)
    {
        frames[i]=-1;
        time[i]=0;
    }

    for(int i=0;i<n;i++)
    {
        int hit=0;
        for(int j=0;j<m;j++)
        {
            if(frames[j] == arr[i])
            {
                counter++;
                time[j] = counter;
                hit=1;
                break;
            }
        }
        if(hit == 0)
        {
            int pos = -1, dist = INT_MAX;
            for(int j=0;j<m;j++)
            {
                if(frames[j] == -1)
                {
                    pos = j;
                    break;
                }
            } 
            if(pos == -1)
            {
                for(int j =0;j<m;j++)
                {
                    if(time[j] < dist)
                    {
                        dist = time[j];
                        pos = j;
                    }
                }
            }

            frames[pos] = arr[i];
            counter++;
            time[pos] = counter;
            faults++;
        }

        printf("Page %d: [",arr[i]);
        for(int j=0;j<m;j++)
        {
            if(frames[j] != -1)
            {
                printf("%d ",frames[j]);
            }
            else
            {
                printf("  ");
            }
        }
        printf("]\n");
    }

    printf("Total faults: %d",faults);
}
void optimal(int arr[],int n,int m)
{
    int frames[m];
    int faults=0;
    for(int i=0;i<m;i++)
    {
        frames[i] = -1;
    }

    for(int i=0;i<n;i++)
    {
        int empty=-1,hit=0;
        for(int j=0;j<m;j++)
        {
            if(frames[j] == arr[i])
            {
                hit=1;
                break;
            }
            if(empty == -1 && frames[j] == -1)
            {
                empty = j;
            }
        }
        if(hit == 0)
        {
            if(empty != -1)
                frames[empty] = arr[i];
            else
            {
                int farthest = -1,replace=-1;
                for(int j=0;j<m;j++)
                {
                    int k;
                    for(k=i+1;k<n;k++)
                    {
                        if(frames[j] == arr[k])
                        break;
                    }
                    if(k == n)
                    {
                        replace = j;
                        break;
                    }
                    if( k > farthest)
                    {
                        farthest = k;
                        replace = j;
                    }
                }

                frames[replace] = arr[i];
            }
            faults++;
        }

        printf("Page %d: [",arr[i]);
        for(int j=0;j<m;j++)
        {
            if(frames[j]!=-1)
            {
                printf("%d ",frames[j]);
            }
            else
            {
                printf("  ");
            }
        }
        printf("]\n");
    }
    printf("Total page faults: %d\n",faults);
}
void fifo(int arr[],int n, int m)
{
    int frames[m];
    int faults = 0;
    int ind = 0;
    for(int i=0;i<m;i++)
    {
        frames[i]=-1;
    }
    for(int i =0; i<n; i++)
    {
        int hit=0;
        for(int j=0;j<m;j++)
        {
            if(arr[i] == frames[j])
            {
                hit =1;
                break;
            }
        }
        if(hit==0)
        {
            faults++;
            frames[ind] = arr[i];
            ind = (ind + 1) % m;
        }
        printf("Page %d: [", arr[i]);
        for (int j = 0; j < m; j++) {
            if (frames[j] != -1)
                printf("%d ", frames[j]);
            else
                printf("  ");
        }
        printf("]\n");
    }
    printf("Total Page Faults (FIFO): %d\n", faults);
}
int main()
{
    int n,m;
    printf("Enter number of pages and frames:");
    scanf("%d %d",&n,&m);
    int arr[n];
    printf("Enter ref string: ");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&arr[i]);   
    }

    fifo(arr,n,m);

    optimal(arr,n,m);

    lru(arr,n,m);
}