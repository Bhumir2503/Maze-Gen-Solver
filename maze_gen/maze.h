#include <SDL2/SDL.h>
#include "cell.h"
#include <map>
#include <vector>

using namespace std;
#ifndef MAZE_H
#define MAZE_H

//Global constants for setting render resolution
//Use smaller dimensions for debugging
const int WIDTH = 1000, HEIGHT = 1000;
const int cellWidth = 100;
class Maze {
	public:
		Maze();							//Sets initial state of maze and SDL window
		void build_grid();	//Builds the initial grid before maze construction
		void draw_grid();		//Displays grid in SDL window
		void print_graph();	//Displays contents of adjList
		void rand_DFS();		//randomized DFS used to construct min span tree
		void draw_path_solver();

	private:
		int grid[WIDTH][HEIGHT];		//Internal state of grid. Used to display to SDL window
		vector<cell> cells;
		//adjList represents the connected graph of each cell in the grid. This graph is used to 
		//construct a MST that determines the layout of the final maze
		std::map<std::pair<int, int>, std::vector<std::pair<int, int>>> adjList;
		vector<pair<int, int>> centerList;

		SDL_Window* window;
		SDL_Renderer* renderer;
		SDL_Event event;			//Used to poll SDL window
		bool quit = false;		//Used to determine when to kill SDL processes
};

#endif
