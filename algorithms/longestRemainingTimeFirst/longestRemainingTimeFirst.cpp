#include <iostream>
#include <iomanip>

#include "../../include/longestRemainingTimeFirst/longestRemainingTimeFirst.h"

using namespace std;

LRTFScheduler::LRTFScheduler() {
    this->currentTime = 0;  
}

void LRTFScheduler::addProcess(const Process& process) {
    processes.push_back(process);  
}

void LRTFScheduler::execute() {
    int totalProcesses = processes.size();  
    int completed = 0;  
    vector<bool> isCompleted(totalProcesses, false);  

    while (completed != totalProcesses) {
        int longestIndex = -1;  
        int maxRemainingTime = -1;  

       
        for (int i = 0; i < totalProcesses; ++i) {
            if (processes[i].arrivalTime <= currentTime && !isCompleted[i] && processes[i].remainingTime > maxRemainingTime) {
                maxRemainingTime = processes[i].remainingTime;
                longestIndex = i;
            }
        }

        
        if (longestIndex == -1) {
            ganttChart.push_back({-1, ++currentTime});  
            continue;
        }


        Process &longestProcess = processes[longestIndex];
        if (ganttChart.empty() || ganttChart.back().first != longestProcess.id) {
            ganttChart.push_back({longestProcess.id, currentTime});  
        }
        
        longestProcess.remainingTime -= 1;  
        currentTime += 1;  


        if (longestProcess.remainingTime == 0) {
            longestProcess.waitingTime = currentTime - longestProcess.arrivalTime - longestProcess.burstTime;
            longestProcess.turnaroundTime = longestProcess.burstTime + longestProcess.waitingTime;
            isCompleted[longestIndex] = true;  
            completed++;
        }

        ganttChart.push_back({longestProcess.id, currentTime});  
    }
}

void LRTFScheduler::displayResults() const {
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

void LRTFScheduler::displayGanttChart() const {
    cout << "\nGantt Chart:\n";

    
    for (const auto& entry : ganttChart) {
        if (entry.first == -1) {
            cout << "| Idle ";
        } else {
            cout << "| P" << entry.first << " ";
        }
    }
    cout << "|\n";

    
    cout << "0";  
    for (const auto& entry : ganttChart) {
        cout << "    " << entry.second;
    }
    cout << endl;
}