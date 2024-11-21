#include <iostream>
#include <algorithm>
#include <iomanip>

#include "../../include/firstComeFirstServe/firstComeFirstServe.h"

using namespace std;


FCFSScheduler::FCFSScheduler() {
    this->currentTime = 0; 
}

void FCFSScheduler::addProcess(const Process& process) {
    processes.push_back(process); 
}

void FCFSScheduler::execute() {
    sort(processes.begin(), processes.end(), [](const Process& p1, const Process& p2) {
        return p1.arrivalTime < p2.arrivalTime;
    });

    for (auto& process : processes) {
       
        if (currentTime < process.arrivalTime) {
            currentTime = process.arrivalTime; 
        }

        ganttChart.push_back({process.id, currentTime}); 
        currentTime += process.burstTime; 
        ganttChart.push_back({process.id, currentTime}); 

        
        process.waitingTime = currentTime - process.arrivalTime - process.burstTime;
        process.turnaroundTime = process.burstTime + process.waitingTime;
    }
}

void FCFSScheduler::displayResults() const {
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

void FCFSScheduler::displayGanttChart() const {
    
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