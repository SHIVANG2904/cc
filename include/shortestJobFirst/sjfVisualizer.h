#ifndef SJF_VISUALIZER_H
#define SJF_VISUALIZER_H

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../process.h" // Process class definition

// Function to simulate Shortest Job First (SJF) scheduling and visualize the Gantt chart
void runSJFVisualizer(std::vector<Process> processes);

#endif // SJF_VISUALIZER_H
