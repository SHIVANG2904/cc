#include <iostream>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <algorithm>
#include <string>

#include "../../include/longestJobFirst/longestJobFirst.h"
#include "../../include/longestJobFirst/ljfVisualizer.h" 
#include "../include/process.h" 

using namespace std;


void runLJFVisualizer(vector<Process> processes) {
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
        return;
    }

    
    if (TTF_Init() == -1) {
        cout << "SDL_ttf could not initialize! TTF_Error: " << TTF_GetError() << endl;
        return;
    }

    
    SDL_Window* window = SDL_CreateWindow("LJF Visualizer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    if (!window) {
        cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
        return;
    }

    
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << endl;
        return;
    }

    
    SDL_SetRenderDrawColor(renderer, 211, 211, 211, 255); 
    SDL_RenderClear(renderer);

    
    int fontSize = 20;  
    TTF_Font* font = TTF_OpenFont("C:/Windows/Fonts/arial.ttf", fontSize);
    if (!font) {
        cout << "Failed to load font! TTF_Error: " << TTF_GetError() << endl;
        return;
    }

    SDL_Color textColor = {255, 255, 255, 255};  

    
    vector<pair<int, int>> ganttChart; 
    vector<bool> completed(processes.size(), false); 
    int currentTime = 0;

    while (true) {
        
        int maxBurstTime = -1;
        int selectedProcess = -1;

        for (size_t i = 0; i < processes.size(); ++i) {
            if (!completed[i] && processes[i].getArrivalTime() <= currentTime) {
                if (processes[i].getBurstTime() > maxBurstTime) {
                    maxBurstTime = processes[i].getBurstTime();
                    selectedProcess = i;
                }
            }
        }

        
        if (selectedProcess == -1) {
            currentTime++;
            continue;
        }

        
        ganttChart.push_back({processes[selectedProcess].getProcessID(), processes[selectedProcess].getBurstTime()});
        currentTime += processes[selectedProcess].getBurstTime();
        completed[selectedProcess] = true;

        
        if (all_of(completed.begin(), completed.end(), [](bool c) { return c; })) {
            break;
        }
    }

    
    int totalBurstTime = 0;
    for (const auto& process : ganttChart) {
        totalBurstTime += process.second;
    }

    
    int windowWidth = 800;
    int barHeight = 50;
    int barStartX = 50;
    float scalingFactor = (windowWidth - 100) / static_cast<float>(totalBurstTime);

    
    for (size_t i = 0; i < ganttChart.size(); ++i) {
        SDL_Rect bar;
        bar.x = barStartX;
        bar.y = 100;
        bar.w = ganttChart[i].second * scalingFactor; 
        bar.h = barHeight;

        
        SDL_SetRenderDrawColor(renderer, 0, 0, 255 - (i * 30), 255);
        SDL_RenderFillRect(renderer, &bar);

        
        string processText = "P" + to_string(ganttChart[i].first) + " (" + to_string(ganttChart[i].second) + ")";
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, processText.c_str(), textColor);
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

        SDL_Rect textRect;
        textRect.x = bar.x + (bar.w - textSurface->w) / 2;
        textRect.y = bar.y + (bar.h - textSurface->h) / 2;
        textRect.w = textSurface->w;
        textRect.h = textSurface->h;

        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

        
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);

        
        barStartX += bar.w;
    }

    
    SDL_RenderPresent(renderer);

    
    bool quit = false;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
    }

    
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    TTF_Quit();
}

int main() {
    vector<Process> processes;
    processes.push_back(Process(1, 0, 8));  
    processes.push_back(Process(2, 1, 4));  
    processes.push_back(Process(3, 2, 9));  
    processes.push_back(Process(4, 3, 5));  

    runLJFVisualizer(processes);  
    return 0;
}
