#include <SDL2/SDL.h>
#include <map>
#include <vector>
using namespace std;

#ifndef MAZE_H
#define MAZE_H

//Global constants for setting render resolution
//Use smaller dimensions for debugging
//const int WIDTH = 1920, HEIGHT = 1080;

class Maze {
	public:
		Maze();							//Sets initial state of maze and SDL window
		void repeat();
		void blackWindow();
		int Sizebutton_builder();
		void build_grid();	//Builds the initial grid before maze construction
		void print_graph();	//Displays contents of adjList
		void adjMat_Builder();
		void rand_prims(vector<vector<int>>, int);		//randomized DFS used to construct min span tree
		int gen_maze(int[], int);
		int DFS(int);
		void decide();
		void reset();

	private:
		//int grid[WIDTH][HEIGHT];		//Internal state of grid. Used to display to SDL window
		//adjList represents the connected graph of each cell in the grid. This graph is used to 
		//construct a MST that determines the layout of the final maze
		int size;
		int cell;
		vector<int> pathway;
		vector<vector<int>> grid;
		vector<bool> visited;
		vector<pair<int,int>> edges;
		vector<int> weights;
		vector<vector<int>> adjMat; //cost matrix
		vector<vector<int>> realAdjMat; 
		SDL_Window* window;
		SDL_Renderer* renderer;
		SDL_Event event;			//Used to poll SDL window
		bool quit = false;		//Used to determine when to kill SDL processes
};

#endif