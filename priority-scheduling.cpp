#include<iostream>
#include<algorithm>
using namespace std;

struct process
{
    int pid, arrival_time, burst_time, priority, waiting_time, completion_time, turnaround_time;
};

bool compare(process a, process b)
{
    if(a.priority == b.priority)
        return a.arrival_time < b.arrival_time;
    return a.priority < b.priority;
}

int main()
{
    int n, i, j;
    float avg_waiting_time = 0, avg_turnaround_time = 0;
    process p[20];

    cout << "Enter the number of processes: ";
    cin >> n;

    for(i = 0; i < n; i++)
    {
        p[i].pid = i + 1;
        cout << "Enter the arrival time for process P" << p[i].pid << ": ";
        cin >> p[i].arrival_time;
        cout << "Enter the burst time for process P" << p[i].pid << ": ";
        cin >> p[i].burst_time;
        cout << "Enter the priority for process P" << p[i].pid << ": ";
        cin >> p[i].priority;
    }

    //Sorting the processes by priority and arrival time using the compare function
    sort(p, p + n, compare);

    //Calculating waiting time for each process
    p[0].waiting_time = 0;
    for(i = 1; i < n; i++)
    {
        p[i].waiting_time = 0;
        for(j = 0; j < i; j++)
            p[i].waiting_time += p[j].burst_time;
        p[i].waiting_time -= p[i].arrival_time - p[0].arrival_time;
    }

    //Calculating completion time for each process
    p[0].completion_time = p[0].burst_time + p[0].arrival_time;
    for(i = 1; i < n; i++)
        p[i].completion_time = max(p[i].arrival_time, p[i-1].completion_time) + p[i].burst_time;

    //Calculating turnaround time for each process
    for(i = 0; i < n; i++)
        p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;

    //Calculating average waiting time and average turnaround time
    for(i = 0; i < n; i++)
    {
        avg_waiting_time += p[i].waiting_time;
        avg_turnaround_time += p[i].turnaround_time;
    }
    avg_waiting_time /= n;
    avg_turnaround_time /= n;

    //Printing the output
    cout<<"\nProcess\tArrival Time\tBurst Time\tPriority\tWaiting Time\tCompletion Time\tTurnaround Time";
    for(i = 0; i < n; i++)
        cout<<"\nP"<<p[i].pid<<"\t\t"<<p[i].arrival_time<<"\t\t"<<p[i].burst_time<<"\t\t"<<p[i].priority<<"\t\t"<<p[i].waiting_time<<"\t\t"<<p[i].completion_time<<"\t\t"<<p[i].turnaround_time;

    cout << "\n\nAverage Waiting Time: " << avg_waiting_time;
    cout << "\nAverage Turnaround Time: " << avg_turnaround_time;

    return 0;
}
