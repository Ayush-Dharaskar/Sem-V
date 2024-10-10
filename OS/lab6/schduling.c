#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
typedef struct{
    int pid;
    int burst_time;
    int rem_time;
    int comp_time;
    int wait_time;
    int arrival_time;
    int turnaround;
}Process;

int find_shortest(Process* p ,int n, int time)
{
    int mini=INT_MAX;
    int ind=-1;
    for(int i=0;i<n;i++)
    {
        if(p[i].arrival_time <=time && p[i].rem_time < mini && p[i].rem_time >0)
        {
            mini = p[i].rem_time;
            ind =i;
        }
    }
    return ind;
}

void FCFS(Process* p, int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            if(p[j].arrival_time > p[j+1].arrival_time)
            {
                Process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }

    int time=0;
    int total_waiting=0;
    int total_turnaround=0;
    for(int i=0;i<n;i++)
    {
        if(p[i].arrival_time > time)
        {
            time = p[i].arrival_time;
        }

        p[i].rem_time=0;
        time += p[i].burst_time;

        p[i].comp_time = time;
        p[i].turnaround = p[i].comp_time - p[i].arrival_time;
        p[i].wait_time = p[i].turnaround -p[i].burst_time;
        
        total_turnaround += p[i].turnaround;
        total_waiting += p[i].wait_time;

        printf("P%d->%d\n",p[i].pid,time);
    }

        printf("PID\t\tArrival\t\tBurst\t\tcompletion\t\ttwaiting\t\tturnaround\n");
    for(int i=0;i<n;i++)
    {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",p[i].pid,p[i].arrival_time,p[i].burst_time,p[i].comp_time,p[i].wait_time,p[i].turnaround);

    }
    printf("Avg waiting: %.2f",(1.0*total_waiting)/n);
    printf("Avg Turnaround: %.2f",(1.0*total_turnaround)/n);
}
void sjf_non_preemtive(Process* p, int n)
{
    int time=0;
    int done=0;
    int total_waiting=0;
    int total_turnaround = 0;

    while(done != n)
    {
        int ind = find_shortest(p,n,time);
        printf("IND:%d",ind);
        if(ind == -1)
        {
            time++;
            continue;
        }
        p[ind].rem_time=0;
        time+=p[ind].burst_time;


        if(p[ind].rem_time == 0)
        {
            p[ind].comp_time = time;
            p[ind].turnaround = p[ind].comp_time - p[ind].arrival_time;
            p[ind].wait_time = p[ind].turnaround - p[ind].burst_time;
            done++;

            total_turnaround += p[ind].turnaround;
            total_waiting += p[ind].wait_time;

        }
        printf("P%d-> %d\n",p[ind].pid,time);
    }

    printf("PID\tArrival\tBurst\tcompletion\twaiting\tturnaround\n");
    for(int i=0;i<n;i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",p[i].pid,p[i].arrival_time,p[i].burst_time,p[i].comp_time,p[i].wait_time,p[i].turnaround);

    }
    printf("Avg waiting: %.2f",(1.0*total_waiting)/n);
    printf("Avg Turnaround: %.2f",(1.0*total_turnaround)/n);
}
void sjf_preemtive(Process* p, int n)
{
    int time=0;
    int done=0;
    int total_waiting=0;
    int total_turnaround = 0;

    while(done != n)
    {
        int ind = find_shortest(p,n,time);
        printf("IND:%d",ind);
        if(ind == -1)
        {
            time++;
            continue;
        }
        p[ind].rem_time--;
        time++;


        if(p[ind].rem_time == 0)
        {
            p[ind].comp_time = time;
            p[ind].turnaround = p[ind].comp_time - p[ind].arrival_time;
            p[ind].wait_time = p[ind].turnaround - p[ind].burst_time;
            done++;

            total_turnaround += p[ind].turnaround;
            total_waiting += p[ind].wait_time;

        }
        printf("P%d-> %d\n",p[ind].pid,time);
    }

    printf("PID\tArrival\tBurst\tcompletion\twaiting\tturnaround\n");
    for(int i=0;i<n;i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",p[i].pid,p[i].arrival_time,p[i].burst_time,p[i].comp_time,p[i].wait_time,p[i].turnaround);

    }
    printf("Avg waiting: %.2f",(1.0*total_waiting)/n);
    printf("Avg Turnaround: %.2f",(1.0*total_turnaround)/n);
}

void RR(Process* p,int n,int tq)
{
    int time=0;
    int done=0;
    int total_waiting=0;
    int total_turnaround=0;
    int queue[100];
    int in_q[100]={0};
    int front=0,rear=0;

    for(int i=0;i<n;i++)
    {
        if(p[i].arrival_time == 0)
        {
            queue[rear++] = i;
            in_q[i]=1;
        }
    }

    while(done != n)
    {
        if(front == rear)
        {
            time++;
            
            for(int i=0;i<n;i++)
            {
                if (p[i].arrival_time <=time && in_q[i]==0)
                {
                    queue[rear++]=i;
                    in_q[i]=1;
                }
                
            }
        }

        int ind = queue[front++];
        int used =tq;
        while(p[ind].rem_time>0 && used>0)
        {
            p[ind].rem_time--;
            time++;
            used--;

            for(int i=0;i<n;i++)
            {
                if (p[i].arrival_time <=time && in_q[i]==0)
                {
                    queue[rear++]=i;
                    in_q[i]=1;
                }
                
            }
        }
        if(p[ind].rem_time ==0)
        {
            p[ind].comp_time = time;
            p[ind].turnaround = p[ind].comp_time - p[ind].arrival_time;
            p[ind].wait_time = p[ind].turnaround - p[ind].burst_time;
            done++;
            total_waiting += p[ind].wait_time;
            total_turnaround += p[ind].turnaround;
        }
        else{
            queue[rear++] = ind;
        }
        printf("P%d -> %d\n",p[ind].pid,time);
    }
    printf("PID\tArrival\tBurst\tcompletion\twaiting\tturnaround\n");
    for(int i=0;i<n;i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",p[i].pid,p[i].arrival_time,p[i].burst_time,p[i].comp_time,p[i].wait_time,p[i].turnaround);

    }
    printf("Avg waiting: %.2f",(1.0*total_waiting)/n);
    printf("Avg Turnaround: %.2f",(1.0*total_turnaround)/n);
}
int main()
{
    int n,opt;

    printf("1)SJF preemtive\n2)sjf Non preemptive\n3)FCFS\n4)RR\n");
    scanf("%d",&opt);
    printf("Enter n:");
    scanf("%d",&n);
    Process* p = (Process*)malloc(sizeof(Process)*n);
    for(int i=0;i<n;i++)
    {
        p[i].pid = i+1;
        printf("Enter arrival and busrt time for process %d: ",i+1);
        scanf("%d %d",&p[i].arrival_time,&p[i].burst_time);
        p[i].rem_time = p[i].burst_time;
    }
    switch(opt)
    {
        case 1:
            sjf_preemtive(p,n);
            break;
        case 2:
            sjf_non_preemtive(p,n);
        break;
        case 3:
            FCFS(p,n);
        break;
        case 4:
            RR(p,n,2);
            break;

    }
}