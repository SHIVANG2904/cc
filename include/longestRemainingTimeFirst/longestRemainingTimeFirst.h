#ifndef LRTF_H
#define LRTF_H

#include <vector>
#include <utility>

#include "../process.h"

using namespace std;

class LRTFScheduler {
private:
    vector<Process> processes;  
    vector<pair<int, int>> ganttChart;  
    int currentTime;  

public:
    LRTFScheduler();  
    void addProcess(const Process& process);  
    void execute();  
    void displayResults() const; 
    void displayGanttChart() const;  
};

#endif