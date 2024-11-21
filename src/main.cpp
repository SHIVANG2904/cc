#include <iostream>
#include <string>

#include "../include/firstComeFirstServe/firstComeFirstServe.h"
#include "../algorithms/firstComeFirstServe/firstComeFirstServe.cpp"

#include "../include/roundRobin/roundRobin.h"
#include "../algorithms/roundRobin/roundRobin.cpp"

#include "../include/longestJobFirst/longestJobFirst.h"
#include "../algorithms/longestJobFirst/longestJobFirst.cpp"

#include "../include/shortestJobFirst/shortestJobFirst.h"
#include "../algorithms/shortestJobFirst/shortestJobFirst.cpp"

#include "../include/longestRemainingTimeFirst/longestRemainingTimeFirst.h"
#include "../algorithms/longestRemainingTimeFirst/longestRemainingTimeFirst.cpp"

#include "../include/process.h"


#include <cstdlib>  // For system()

using namespace std;

void runFirstComeFirstServeTestCases() {
    cout << "Running First Come First Serve (FCFS) Scheduler Test Cases\n";

    cout << "Test Case 1: \n";
    FCFSScheduler fcfs1;
    fcfs1.addProcess(Process(1, 0, 5));   // P1 arrives at 0, burst time = 5
    fcfs1.addProcess(Process(2, 2, 3));   // P2 arrives at 2, burst time = 3
    fcfs1.addProcess(Process(3, 4, 8));   // P3 arrives at 4, burst time = 8
    fcfs1.addProcess(Process(4, 6, 2));   // P4 arrives at 6, burst time = 2
    fcfs1.execute();
    fcfs1.displayResults();
    fcfs1.displayGanttChart();

    cout<<endl;
    cout<<"----------------------------------------------------------------------------"<<endl;

    cout << "Test Case 2: \n";
    FCFSScheduler fcfs2;
    fcfs2.addProcess(Process(1, 0, 10)); // Process 1: arrival time = 0, burst time = 10
    fcfs2.addProcess(Process(2, 2, 4));  // Process 2: arrival time = 2, burst time = 4
    fcfs2.addProcess(Process(3, 3, 6));  // Process 3: arrival time = 3, burst time = 6
    fcfs2.addProcess(Process(4, 5, 9));  // Process 4: arrival time = 5, burst time = 9
    fcfs2.execute();
    fcfs2.displayResults();
    fcfs2.displayGanttChart();

    // Run FCFS Visualizer (SDL)
    // Save the processes data to a temporary file or pass them as command-line arguments
    // system("g++ -I SDL2/include -L SDL2/lib -o firstComeFirstServeVisualizer algorithms/firstComeFirstServe/firstComeFirstServeVisualizer.cpp -lmingw32 -lSDL2main -lSDL2");
    // system("./firstComeFirstServeVisualizer");
}

void runRoundRobinTestCases() {
    cout << "Running Round Robin Scheduler (RR) Test Cases\n";
    
    cout << "Test Case 1: \n";
    RoundRobinScheduler rr1(4);        // Time quantum of 4
    rr1.addProcess(Process(1, 0, 5));  // Process 1: arrival time = 0, burst time = 5
    rr1.addProcess(Process(2, 1, 8));  // Process 2: arrival time = 1, burst time = 8
    rr1.addProcess(Process(3, 2, 6));  // Process 3: arrival time = 2, burst time = 6
    rr1.execute();
    rr1.displayResults();
    rr1.displayGanttChart();

    cout<<endl;
    cout<<"----------------------------------------------------------------------------"<<endl;

    cout << "\nTest Case 2: \n";
    RoundRobinScheduler rr2(2);        // Time quantum of 2
    rr2.addProcess(Process(1, 0, 10)); // Process 1: arrival time = 0, burst time = 10
    rr2.addProcess(Process(2, 2, 4));  // Process 2: arrival time = 2, burst time = 4
    rr2.addProcess(Process(3, 3, 6));  // Process 3: arrival time = 3, burst time = 6
    rr2.addProcess(Process(4, 5, 9));  // Process 4: arrival time = 5, burst time = 9
    rr2.execute();
    rr2.displayResults();
    rr2.displayGanttChart();
}

void runLongestJobFirstTestCases() {
    cout << "Running Longest Job First (LJF) Scheduler Test Cases\n";

    cout << "Test Case 1:\n";
    LJFScheduler ljf1;
    ljf1.addProcess(Process(1, 1, 2));  // Process 1: arrival time = 1, burst time = 2
    ljf1.addProcess(Process(2, 2, 5));  // Process 2: arrival time = 2, burst time = 5
    ljf1.addProcess(Process(3, 3, 3));  // Process 3: arrival time = 3, burst time = 3
    ljf1.addProcess(Process(4, 4, 8));  // Process 4: arrival time = 4, burst time = 8
    ljf1.execute();
    ljf1.displayResults();
    ljf1.displayGanttChart();

    cout<<endl;
    cout<<"----------------------------------------------------------------------------"<<endl;

    cout << "Test Case 2:\n";
    LJFScheduler ljf2;
    ljf2.addProcess(Process(1, 1, 2)); // Process 1: arrival time = 1, burst time = 2
    ljf2.addProcess(Process(2, 2, 4)); // Process 2: arrival time = 2, burst time = 4
    ljf2.addProcess(Process(3, 3, 6)); // Process 3: arrival time = 3, burst time = 6
    ljf2.addProcess(Process(4, 4, 8)); // Process 4: arrival time = 4, burst time = 8
    ljf2.execute();
    ljf2.displayResults();
    ljf2.displayGanttChart();
}

void runShortestJobFirstTestCases() {
    cout << "Running Shortest Job First (SJF) Scheduler Test Cases\n";

    cout << "Test Case 1:\n";
    SJFScheduler sjf1;
    sjf1.addProcess(Process(1, 0, 6));   // P1 arrives at 0, burst time = 6
    sjf1.addProcess(Process(2, 1, 8));   // P2 arrives at 1, burst time = 8
    sjf1.addProcess(Process(3, 2, 7));   // P3 arrives at 2, burst time = 7
    sjf1.addProcess(Process(4, 3, 3));   // P4 arrives at 3, burst time = 3
    sjf1.execute();
    sjf1.displayResults();
    sjf1.displayGanttChart();

    cout<<endl;
    cout<<"----------------------------------------------------------------------------"<<endl;

    cout << "Test Case 2:\n";
    SJFScheduler sjf2;
    sjf2.addProcess(Process(1, 0, 10)); // Process 1: arrival time = 0, burst time = 10
    sjf2.addProcess(Process(2, 2, 4));  // Process 2: arrival time = 2, burst time = 4
    sjf2.addProcess(Process(3, 3, 6));  // Process 3: arrival time = 3, burst time = 6
    sjf2.addProcess(Process(4, 5, 9));  // Process 4: arrival time = 5, burst time = 9
    sjf2.execute();
    sjf2.displayResults();
    sjf2.displayGanttChart();
}

void runLongestRemainingTimeFirstTestCases() {
    cout << "Running Longest Remaining Time First (LRTF) Scheduler Test Cases\n";

    LRTFScheduler lrtf1;
    lrtf1.addProcess(Process(1, 1, 2));   // P1: Arrival time = 0, Burst time = 5
    lrtf1.addProcess(Process(2, 2, 4));   // P2: Arrival time = 1, Burst time = 8
    lrtf1.addProcess(Process(3, 3, 6));   // P3: Arrival time = 2, Burst time = 6
    lrtf1.addProcess(Process(4, 4, 8));   // P3: Arrival time = 2, Burst time = 6
    lrtf1.execute();
    lrtf1.displayResults();
    lrtf1.displayGanttChart();

    cout<<endl;
    cout<<"----------------------------------------------------------------------------"<<endl;

    LRTFScheduler lrtf2;
    lrtf2.addProcess(Process(1, 0, 10)); // Process 1: arrival time = 0, burst time = 10
    lrtf2.addProcess(Process(2, 2, 4));  // Process 2: arrival time = 2, burst time = 4
    lrtf2.addProcess(Process(3, 3, 6));  // Process 3: arrival time = 3, burst time = 6
    lrtf2.addProcess(Process(4, 5, 9));  // Process 4: arrival time = 5, burst time = 9
    lrtf2.execute();
    lrtf2.displayResults();
    lrtf2.displayGanttChart();
}

int main() {
    string input;
    cout << "Enter scheduling algorithm to run (fcfs, sjf, rr, ljf, lrtf): ";
    cin >> input;

    if (input == "fcfs") { runFirstComeFirstServeTestCases(); } 
    else if (input == "rr") { runRoundRobinTestCases(); } 
    else if (input == "ljf") { runLongestJobFirstTestCases(); } 
    else if (input == "sjf") { runShortestJobFirstTestCases(); } 
    else if (input == "lrtf") { runLongestRemainingTimeFirstTestCases(); }
    
    return 0;
}