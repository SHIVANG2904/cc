all:
	g++ -I SDL2/include -L SDL2/lib -o fcfs algorithms/firstComeFirstServe/firstComeFirstServeVisualizer.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf
	
# all:
# 	g++ -I SDL2/include -L SDL2/lib -o ljf algorithms/longestJobFirst/ljfVisualizer.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf
	
# all:
# 	g++ -I SDL2/include -L SDL2/lib -o lrtf algorithms/longestRemainingTimeFirst/lrtfVisualizer.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf

# all:
# 	g++ -I SDL2/include -L SDL2/lib -o rr algorithms/roundRobin/rrVisualizer.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf

# all:
# 	g++ -I SDL2/include -L SDL2/lib -o sjf algorithms/shortestJobFirst/sjfVisualizer.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf














# # Compiler and flags
# CXX = g++
# CXXFLAGS = -I SDL2/include -L SDL2/lib -lmingw32 -lSDL2main -lSDL2

# # Source files for scheduling algorithms and visualizers
# SCHEDULER_SRC = sdl.cpp
# FCFS_VISUALIZER_SRC = algorithms/firstComeFirstServe/firstComeFirstServeVisualizer.cpp

# # Output binaries
# OUTPUT_SDL = sdl
# FCFS_VISUALIZER_OUTPUT = fcfs_visualizer

# # Default target
# all:
#     $(CXX) $(CXXFLAGS) -o $(OUTPUT_SDL) $(SCHEDULER_SRC)

# # Compile FCFS visualizer
# firstComeFirstServeVisualizer:
#     $(CXX) $(CXXFLAGS) -o $(FCFS_VISUALIZER_OUTPUT) $(FCFS_VISUALIZER_SRC)