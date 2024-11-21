#include <iostream>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <string>
#include "../../include/firstComeFirstServe/firstComeFirstServeVisualizer.h" 
#include "../include/process.h" 

using namespace std;

void runFCFSVisualizer(const vector<Process>& processes) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
        return;
    }

    if (TTF_Init() == -1) {
        cout << "SDL_ttf could not initialize! TTF_Error: " << TTF_GetError() << endl;
        return;
    }

    SDL_Window* window = SDL_CreateWindow("FCFS Visualizer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
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

    int currentTime = 0;
    int barHeight = 50;

    for (size_t i = 0; i < processes.size(); ++i) {
        SDL_Rect bar;
        bar.x = currentTime * 50;  
        bar.y = 100;               
        bar.w = processes[i].getBurstTime() * 50;  
        bar.h = barHeight;         
        
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);  
        SDL_RenderFillRect(renderer, &bar);  
        
        string processIDText = "P" + to_string(processes[i].getProcessID()) + " (" + to_string(processes[i].getBurstTime()) + ")";
        
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, processIDText.c_str(), textColor);
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        
        SDL_Rect textRect;
        textRect.x = bar.x + (bar.w - textSurface->w) / 2;
        textRect.y = bar.y + (bar.h - textSurface->h) / 2;
        textRect.w = textSurface->w;
        textRect.h = textSurface->h;

        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);  
        
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);

        currentTime += processes[i].getBurstTime();
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
    processes.push_back(Process(1, 0, 5));
    processes.push_back(Process(2, 2, 3));
    processes.push_back(Process(3, 4, 8));
    processes.push_back(Process(4, 6, 2));

    runFCFSVisualizer(processes);  

    return 0;
}