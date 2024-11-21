#include <iostream>
#include <iomanip>

#include "../../include/longestJobFirst/longestJobFirst.h"

using namespace std;

LJFScheduler::LJFScheduler() {
    this->currentTime = 0;
}

void LJFScheduler::addProcess(const Process& process) {
    
    processes.push_back(process);
}

void LJFScheduler::execute() {
    
    int completedProcesses = 0;

    while (completedProcesses < processes.size()) {
        int longestIndex = -1;
        int longestBurst = -1;

        
        for (int i = 0; i < processes.size(); ++i) {
            if (processes[i].remainingTime > 0 && processes[i].arrivalTime <= currentTime && processes[i].burstTime > longestBurst) {
                longestBurst = processes[i].burstTime;
                longestIndex = i;
            }
        }

        if (longestIndex != -1) {
            
            Process &process = processes[longestIndex];
            currentTime += process.remainingTime;  
            process.waitingTime = currentTime - process.arrivalTime - process.burstTime;
            process.turnaroundTime = process.burstTime + process.waitingTime;
            process.remainingTime = 0;             
            ganttChart.push_back({process.id, currentTime}); 
            ++completedProcesses;
        } else {
            
            int nextArrivalTime = 1e9;
            for (const auto& process : processes) {
                if (process.remainingTime > 0) {
                    nextArrivalTime = min(nextArrivalTime, process.arrivalTime);
                }
            }
            currentTime = max(currentTime, nextArrivalTime);
        }
    }
}

void LJFScheduler::displayResults() const {
    
    cout << setw(10) << "Process" 
         << setw(15) << "Arrival Time" 
         << setw(15) << "Burst Time" 
         << setw(15) << "Waiting Time" 
         << setw(15) << "Turnaround Time" << "\n";
    
    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;

    
    for (const auto& process : processes) {
        cout << setw(10) << "P" + to_string(process.id)
             << setw(15) << process.arrivalTime
             << setw(15) << process.burstTime
             << setw(15) << process.waitingTime
             << setw(15) << process.turnaroundTime << "\n";

        
        totalWaitingTime += process.waitingTime;
        totalTurnaroundTime += process.turnaroundTime;
    }

    
    double avgWaitingTime = static_cast<double>(totalWaitingTime) / processes.size();
    double avgTurnaroundTime = static_cast<double>(totalTurnaroundTime) / processes.size();

    cout << "\nAverage Waiting Time: " << avgWaitingTime << endl;
    cout << "Average Turnaround Time: " << avgTurnaroundTime << endl;
}

const vector<pair<int, int>>& LJFScheduler::getGanttChart() const {
    return ganttChart;
}

void LJFScheduler::displayGanttChart() const {
    
    cout << "\nGantt Chart:\n";
    for (const auto& entry : ganttChart) {
        cout << "| P" << entry.first << " ";  
    }
    cout << "|\n";

    
    cout << "0"; 
    for (const auto& entry : ganttChart) {
        cout << "    " << entry.second;  
    }
    cout << endl;
}