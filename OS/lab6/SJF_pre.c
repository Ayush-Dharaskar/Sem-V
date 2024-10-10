#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

typedef struct{
    int pid;
    int arrival_time;
    int burst_time;
    int rem_time;
    int wait_time;
    int completion_time;
    int turnaround_time;
    int priority;
}Process;

void print(int arr[], int n)
{
    for(int i=0;i<n;i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
}

int compare(const void *a,const void*b)
{
    Process * p1 = (Process*) a;
    Process * p2 = (Process*) b;
    if(p1->arrival_time == p2->arrival_time)
    {
        return p1->priority - p2->priority;
    }
    return p1->arrival_time - p2->arrival_time;
}
void priority(Process *p,int n)
{
    qsort(p,n,sizeof(Process),compare);
    int time =0;
}
void RR(Process *p,int n,int quantum)
{
    int time=0;
    int done=0;
    int total_waiting=0;
    int total_turnaround=0;
    int queue[100],front=0,rear=0;
    int in_q[100]={0};

    for(int i=0;i<n;i++)
    {
        if(p[i].arrival_time == 0)
        {
            queue[rear++] = i;
            in_q[i] = 1;
        }
    }

    while(done != n)
    {
        if(front == rear)
        {
            time++;
            for(int i=0;i<n;i++)
            {
                if(p[i].arrival_time == time && in_q[i] ==0)
                {
                    queue[rear++] = i;
                    in_q[i] = 1;
                }
            }
        }

        int ind = queue[front++];
        int used = quantum;
        while(p[ind].rem_time > 0 && used>0)
        {
            p[ind].rem_time--;
            used--;
            time++;

            for(int i=0;i<n;i++)
            {
                if(p[i].arrival_time == time && in_q[i] == 0)
                {
                    queue[rear++] = i;
                    in_q[i] = 1;
                }
            }
        }
        if(p[ind].rem_time >0)
        {
            queue[rear++] = ind;
        }
        else
        {
            p[ind].completion_time = time;
            p[ind].turnaround_time = p[ind].completion_time - p[ind].arrival_time;
            p[ind].wait_time = p[ind].turnaround_time - p[ind].burst_time;
            done++;
            total_waiting += p[ind].wait_time;
            total_turnaround += p[ind].turnaround_time;
        }
        printf("P%d -> %d\n",p[ind].pid,time);
    }
    printf("\nPID\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].arrival_time, p[i].burst_time,
               p[i].completion_time, p[i].wait_time, p[i].turnaround_time);
    }
    printf("Avg waiting time: %.2f\n", (1.0 * total_waiting) / n);
    printf("Avg turnaround time: %.2f\n", (1.0 * total_turnaround) / n);
}
int find_shortest(Process* p,int n,int cur)
{
    int shortest=INT_MAX;
    int ind=-1;
    for(int i=0;i<n;i++)
    {
        if(p[i].arrival_time <= cur && shortest > p[i].rem_time && p[i].rem_time > 0)
        {   
            shortest = p[i].rem_time;
            ind = i;
            
        }
    }
    return ind;
}

void sjf_non_preemptive(Process* p,int n)
{


    int time = 0;
    int done =0;
    int total_waiting =0 ;
    int total_turnaround =0;

    while(done != n)
    {
        int ind = find_shortest(p,n,time);

        if (ind == -1)
        {
            time++;
            continue;
        }

        p[ind].rem_time =0;
        time+= p[ind].burst_time;

        if(p[ind].rem_time ==0)
        {
            p[ind].completion_time = time;
            p[ind].turnaround_time = p[ind].completion_time - p[ind].arrival_time;
            p[ind].wait_time =  p[ind].turnaround_time - p[ind].burst_time;
            done++;

            total_waiting += p[ind].wait_time;
            total_turnaround += p[ind].turnaround_time;
        }
        printf("P%d -> %d\n",p[ind].pid,time);
    }
    printf("\nPID\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].arrival_time, p[i].burst_time,
               p[i].completion_time, p[i].wait_time, p[i].turnaround_time);
    }

    printf("Avg waiting time : %.2f\n", (1.0 * total_waiting) / n);
    printf("Avg turnaround time : %.2f\n", (1.0 * total_turnaround) / n);
}

void sjf_preemptive(Process* p,int n)
{
    int time = 0;
    int done =0;
    int total_waiting =0 ;
    int total_turnaround =0;

    while(done != n)
    {
        int ind = find_shortest(p,n,time);

        if (ind == -1)
        {
            time++;
            continue;
        }

        p[ind].rem_time--;
        time++;

        if(p[ind].rem_time ==0)
        {
            p[ind].completion_time = time;
            p[ind].turnaround_time = p[ind].completion_time - p[ind].arrival_time;
            p[ind].wait_time =  p[ind].turnaround_time - p[ind].burst_time;
            done++;

            total_waiting += p[ind].wait_time;
            total_turnaround += p[ind].turnaround_time;
        }

        printf("P%d -> %d\n",p[ind].pid,time);

    }
    printf("\nPID\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].arrival_time, p[i].burst_time,
               p[i].completion_time, p[i].wait_time, p[i].turnaround_time);
    }
    printf("waiting time : %d\n",total_turnaround);

    printf("turnaroundtime : %d\n",n);
    printf("Avg waiting time : %.2f\n",(1.0*total_waiting)/n);
    printf("Avg turnaroundtime : %.2f\n",(1.0*total_turnaround)/n);
}

int arrival(const void *a,const void*b)
{
    Process* p1 = (Process*)a;
    Process* p2 = (Process*)b;

    return p1->arrival_time - p2->arrival_time;
}
void FCFS(Process * p,int n)
{

    int time= 0;
    int done =0;
    int total_waiting=0;
    int total_turnaround=0;

    qsort(p,n,sizeof(Process),arrival);

        for(int i=0;i<n;i++)
        {
            if(time < p[i].arrival_time)
            {
                time  = p[i].arrival_time;
            }
            time += p[i].burst_time;
            p[i].rem_time =0;


            p[i].completion_time = time;
            p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
            p[i].wait_time = p[i].turnaround_time - p[i].burst_time;
            done++;

            total_turnaround += p[i].turnaround_time;
            total_waiting +=p[i].wait_time;
            printf("P%d -> %d\n",p[i].pid,time);
        }
        //  printf("P%d -> %d\n",p[i].pid,time);

    printf("\nPID\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].arrival_time, p[i].burst_time,
               p[i].completion_time, p[i].wait_time, p[i].turnaround_time);
    }

    printf("Avg waiting time : %.2f\n",(1.0*total_waiting)/n);
    printf("Avg turnaroundtime : %.2f\n",(1.0*total_turnaround)/n);
}


int main()
{
    int opt;
    while(1)
    {
        int n;
        printf("1) SJF preemptive\n2) Round Robin\n3)priority\n4)SFJ non preemptive\n5)FCFS\n6)Exit");
        scanf("%d",&opt);
        int quantum=0;
        printf("Enter number of processes: ");
        scanf("%d",&n);
        Process* p = (Process*) malloc(sizeof(Process) * n);

        for(int i=0;i<n;i++)
        {
            p[i].pid = i+1;
            printf("Enter Arrival Time, Burst Time for process %d: ",i+1);
            scanf("%d %d", &p[i].arrival_time, &p[i].burst_time);
            p[i].rem_time = p[i].burst_time;
        }
        switch(opt){

            case 1:

                sjf_preemptive(p,n);
            break;

            case 2:
                printf("Enter quantum: ");
                scanf("%d",&quantum);
                RR(p,n,quantum);
            break;

            case 3:
                for(int i=0;i<n;i++)
                {
                    printf("Enter priority for process %d: ",i+1);
                    scanf("%d",&p[i].priority);
                }
                priority(p,n);
            break;

            case 4:
                sjf_non_preemptive(p,n);
            break;

            case 5:
                FCFS(p,n);
            break;

            case 6:
                exit(0);
            break;

        }
    }
    return 0;
}