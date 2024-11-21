#ifndef RRVISUALIZER_H
#define RRVISUALIZER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <string>
#include "../process.h" 


void runRRVisualizer(std::vector<Process> processes, int quantum);

#endif 
