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
}Process;

void print(int arr[], int n)
{
    for(int i=0;i<n;i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
}
void RR(Process *p,int n,int quantum)
{

    int time = 0;
    int done = 0;
    int total_waiting = 0;
    int total_turnaround = 0;

    int queue[100], front = 0, rear = 0;
    int in_queue[100] = {0}; // Array to check if a process is in the queue

    // Enqueue processes that arrive at time 0
    for (int i = 0; i < n; i++) {
        if (p[i].arrival_time == 0) {
            queue[rear++] = i;
            in_queue[i] = 1;
        }
    }

    while (done != n) {
        // If the queue is empty (no process is ready), increment time
        if (front == rear) {
            time++;
            // Check for processes that arrive at this time and enqueue them
            for (int i = 0; i < n; i++) {
                if (p[i].arrival_time == time && in_queue[i] == 0) {
                    queue[rear++] = i;
                    in_queue[i] = 1;
                }
            }
            continue;
        }

        // Dequeue the process
        int ind = queue[front++];

        // Process executes for the quantum or its remaining time, whichever is smaller
        int exec_time = (p[ind].rem_time > quantum) ? quantum : p[ind].rem_time;
        time += exec_time;
        p[ind].rem_time -= exec_time;

        // Check for new arrivals during the execution
        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= time && in_queue[i] == 0) {
                queue[rear++] = i;
                in_queue[i] = 1;
            }
        }

        // If the process is not finished, re-enqueue it
        if (p[ind].rem_time > 0) {
            queue[rear++] = ind;
        } else {
            // Process finished execution
            p[ind].completion_time = time;
            p[ind].turnaround_time = p[ind].completion_time - p[ind].arrival_time;
            p[ind].wait_time = p[ind].turnaround_time - p[ind].burst_time;
            done++;
            total_waiting += p[ind].wait_time;
            total_turnaround += p[ind].turnaround_time;
        }
        printf("P%d -> %d\n", p[ind].pid, time);
    }

    // Display the results
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
int main()
{
    int opt;
    while(1)
    {
        int n;
        printf("1) SJF preemptive\n2) Round Robin\n");
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

        }
    }
    return 0;
}