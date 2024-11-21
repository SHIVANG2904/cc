#ifndef LJF_H
#define LJF_H

#include <vector>
#include <utility>

#include "../process.h"

using namespace std;

class LJFScheduler {
private:
    vector<Process> processes;                    
    vector<pair<int, int>> ganttChart;            
    int currentTime;                              

public:
    LJFScheduler();                               
    void addProcess(const Process& process);      
    void execute();                               
    void displayResults() const;                  
    void displayGanttChart() const;               
    const vector<pair<int, int>>& getGanttChart() const;
};

#endif