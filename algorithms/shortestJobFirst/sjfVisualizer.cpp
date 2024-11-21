#include <iostream>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>

#include "../../include/shortestJobFirst/shortestJobFirst.h"
#include "../../include/shortestJobFirst/sjfVisualizer.h" 
#include "../include/process.h" 

using namespace std;


void runSJFVisualizer(vector<Process> processes) {
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
        return;
    }

    if (TTF_Init() == -1) {
        cout << "SDL_ttf could not initialize! TTF_Error: " << TTF_GetError() << endl;
        return;
    }

    
    int windowWidth = 1200;  
    int windowHeight = 400;  
    int margin = 10;  

    
    SDL_Window* window = SDL_CreateWindow("SJF Visualizer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
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

    
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        if (a.getArrivalTime() == b.getArrivalTime()) {
            return a.getBurstTime() < b.getBurstTime();
        }
        return a.getArrivalTime() < b.getArrivalTime();
    });

    int currentTime = 0;
    vector<pair<int, int>> ganttChart; 
    vector<bool> completed(processes.size(), false);

    
    while (true) {
        
        vector<int> readyQueue;
        for (size_t i = 0; i < processes.size(); ++i) {
            if (processes[i].getArrivalTime() <= currentTime && !completed[i]) {
                readyQueue.push_back(i);
            }
        }

        if (readyQueue.empty()) {
            
            int nextArrival = 1e9;
            for (size_t i = 0; i < processes.size(); ++i) {
                if (!completed[i]) {
                    nextArrival = min(nextArrival, processes[i].getArrivalTime());
                }
            }
            currentTime = nextArrival;
            continue;
        }

        
        int shortestProcess = readyQueue[0];
        for (int i : readyQueue) {
            if (processes[i].getBurstTime() < processes[shortestProcess].getBurstTime()) {
                shortestProcess = i;
            }
        }

        
        ganttChart.push_back({processes[shortestProcess].getProcessID(), processes[shortestProcess].getBurstTime()});
        currentTime += processes[shortestProcess].getBurstTime();
        completed[shortestProcess] = true;

        
        bool allCompleted = true;
        for (bool c : completed) {
            if (!c) {
                allCompleted = false;
                break;
            }
        }
        if (allCompleted) {
            break;
        }
    }

    
    int totalBurstTime = 0;
    for (auto& p : ganttChart) {
        totalBurstTime += p.second;
    }
    float scalingFactor = (windowWidth - 100) / static_cast<float>(totalBurstTime);

    
    int barHeight = 50;
    int barStartX = 50;
    int lineHeight = 100; 

    
    int processCountInLine = 0;

   
    for (size_t i = 0; i < ganttChart.size(); ++i) {
        SDL_Rect bar;
        bar.x = barStartX;
        bar.y = lineHeight;
        bar.w = ganttChart[i].second * scalingFactor; 
        bar.h = barHeight;

        
        SDL_SetRenderDrawColor(renderer, 0, 255 - (i * 30), 0, 255); 
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

        
        barStartX += bar.w + margin;
        processCountInLine++;

        
        if (processCountInLine >= 4) {
            barStartX = 50;  
            lineHeight += barHeight + 10;  
            processCountInLine = 0;  
        }
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
    processes.push_back(Process(1, 0, 10));  
    processes.push_back(Process(2, 1, 4));   
    processes.push_back(Process(3, 2, 7));   
    processes.push_back(Process(4, 3, 5));   
    processes.push_back(Process(5, 4, 6));  
    processes.push_back(Process(6, 5, 8));   

    runSJFVisualizer(processes);  

    return 0;
}