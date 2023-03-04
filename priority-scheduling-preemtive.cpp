#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct process {
    int id;  // process id
    int at;  // arrival time
    int bt;  // burst time
    int pt;  // priority
    int rt;  // remaining time
    int wt;  // waiting time
    int ct;  // completion time
    int tat; // turnaround time
};

struct compare {
    bool operator()(const process& p1, const process& p2) {
        return p1.pt > p2.pt;
    }
};

void calculate(process p[], int n) {
    priority_queue<process, vector<process>, compare> pq;

    int time = 0;
    int completed = 0;
    int idx = 0;

    // Add all processes to the queue
    while (completed != n) {
        while (idx < n && p[idx].at <= time) {
            pq.push(p[idx]);
            idx++;
        }

        // If the queue is empty, idle until next process arrives
        if (pq.empty()) {
            time = p[idx].at;
            continue;
        }

        // Process the top process in the queue
        process curr = pq.top();
        pq.pop();

        // Calculate waiting time
        curr.wt = time - curr.at;

        // Calculate completion time and turnaround time
        curr.ct = time + curr.rt;
        curr.tat = curr.ct - curr.at;

        // Update time and remaining time
        time = curr.ct;
        curr.rt = 0;

        // Print process details
        cout << "Process " << curr.id << ":\n";
        cout << "Arrival Time: " << curr.at << "\n";
        cout << "Burst Time: " << curr.bt << "\n";
        cout << "Priority: " << curr.pt << "\n";
        cout << "Waiting Time: " << curr.wt << "\n";
        cout << "Completion Time: " << curr.ct << "\n";
        cout << "Turnaround Time: " << curr.tat << "\n\n";

        completed++;
    }
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    process p[n];
    for (int i = 0; i < n; i++) {
        cout << "Enter arrival time, burst time, and priority of process " << i + 1 << ": ";
        cin >> p[i].at >> p[i].bt >> p[i].pt;
        p[i].id = i + 1;
        p[i].rt = p[i].bt;
    }

    calculate(p, n);

    return 0;
}
