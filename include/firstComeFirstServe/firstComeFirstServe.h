#ifndef FCFS_H
#define FCFS_H

#include <vector>
#include <utility>

#include "../process.h"

using namespace std;

class FCFSScheduler {
private:
    vector<Process> processes; 
    vector<pair<int, int>> ganttChart; 
    int currentTime; 

public:
    FCFSScheduler(); 
    void addProcess(const Process& process); 
    void execute(); 
    void displayResults() const; 
    void displayGanttChart() const; 
};

#endif