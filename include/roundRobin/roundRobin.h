#ifndef ROUND_ROBIN_H
#define ROUND_ROBIN_H

#include <vector>
#include <utility>

#include "../process.h"

using namespace std;

class RoundRobinScheduler {
private:
    int timeQuantum;                    
    vector<Process> processes;          
    vector<pair<int, int>> ganttChart;  
    int currentTime;                   

public:
    RoundRobinScheduler(int timeQuantum);      
    void addProcess(const Process& process);  
    void execute();                            
    void displayResults() const;              
    void displayGanttChart() const;            
};

#endif