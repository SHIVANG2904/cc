#include <iostream>
#include <iomanip>

#include "../../include/roundRobin/roundRobin.h"

using namespace std;

RoundRobinScheduler::RoundRobinScheduler(int timeQuantum) {
    
    this->timeQuantum = timeQuantum;
    this->currentTime = 0;
}

void RoundRobinScheduler::addProcess(const Process& process) {
    
    processes.push_back(process);
}

void RoundRobinScheduler::execute() {
    
    bool done;
    while (true) {
        done = true;  
        for (auto &process : processes) {
            if (process.remainingTime > 0) {
                
                done = false;

                if (process.remainingTime > timeQuantum) {
                    
                    currentTime += timeQuantum;
                    process.remainingTime -= timeQuantum;

                    
                    ganttChart.push_back({process.id, currentTime});
                } else {
                    
                    currentTime += process.remainingTime;
                    process.waitingTime = currentTime - process.arrivalTime - process.burstTime;
                    process.turnaroundTime = process.burstTime + process.waitingTime;
                    process.remainingTime = 0;

                    
                    ganttChart.push_back({process.id, currentTime});
                }
            }
        }

        
        if (done) break;
    }
}

void RoundRobinScheduler::displayResults() const {
    
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

void RoundRobinScheduler::displayGanttChart() const {
    
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