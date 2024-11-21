#ifndef SJF_H
#define SJF_H

#include <vector>
#include <utility>

#include "../process.h"

using namespace std;

class SJFScheduler {
private:
    vector<Process> processes;          
    vector<pair<int, int>> ganttChart;  
    int currentTime;                    

public:
    SJFScheduler();                             
    void addProcess(const Process& process);   
    void execute();                             
    void displayResults() const;               
    void displayGanttChart() const;             
};

#endif