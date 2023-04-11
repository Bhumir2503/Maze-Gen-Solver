#include "maze.h"
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

Maze::Maze()
{
	// Open SDL
	SDL_Init(SDL_INIT_VIDEO);
	// Create window and renderer
	SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer);
	// Make renderer black
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	// These function calls are for testing only
	build_grid();
	print_graph();
	draw_grid();
	draw_path_solver();

	// Hold screen until exit
	while (quit == false)
	{
		if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
		{
			quit = true;
			break;
		}
	}

	// Upon quit, clean up SDL resources
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

// Traverses SDL window region pixel by pixel. Creates a grid where each cell
// is 10x10 pixels. The center pixel of each cell is treated as a vertex
// in a graph and an edge between every neighbor vertex is inserted into
// the adjacency list
void Maze::build_grid()
{
	for (size_t i = 0; i < WIDTH; ++i)
	{
		for (size_t j = 0; j < HEIGHT; ++j)
		{
			if (i % cellWidth == 0 || j % cellWidth == 0)
			{
				grid[i][j] = 1;
			}
			// else if((i % cellWidth >= (cellWidth/2 -10) && i % cellWidth <= (cellWidth/2 +10) )||(j % cellWidth >= (cellWidth/2 -10) && j % cellWidth <= (cellWidth/2 +10) )){
			//	grid[i][j] = 2; //have a 3 pixel path in each cell in the 4th pixel row
			// }
			else if (i % cellWidth >= (cellWidth / 2 - 10) && i % cellWidth <= (cellWidth / 2 + 10) && j % cellWidth >= (cellWidth / 2 - 10) && j % cellWidth <= (cellWidth / 2 + 10))
			{
				grid[i][j] = 100;
			}
			else if ((i % cellWidth >= (cellWidth / 2 - 10) && i % cellWidth <= (cellWidth / 2 + 10)) && (j % cellWidth <= 50))
			{ // up
				grid[i][j] = 2;
			}
			else if ((i % cellWidth >= (cellWidth / 2 - 10) && i % cellWidth <= (cellWidth / 2 + 10)) && (j % cellWidth >= 50))
			{ // down
				grid[i][j] = 3;
			}
			else if ((i % cellWidth <= (cellWidth / 2 - 10)) && (j % cellWidth >= (cellWidth / 2 - 10) && j % cellWidth <= (cellWidth / 2 + 10)))
			{ // left
				grid[i][j] = 4;
			}
			else if ((i % cellWidth >= (cellWidth / 2 + 10)) && (j % cellWidth >= (cellWidth / 2 - 10) && j % cellWidth <= (cellWidth / 2 + 10))) // center +- (size/20 / 2)
			{																																	  // left
				grid[i][j] = 5;
			}
			else
			{
				grid[i][j] = 0;
			}

			// This condition only passes for pixels in the center of each cell
			if (i % 50 == 0 && i % cellWidth != 0 && j % 50 == 0 && j % cellWidth != 0)
			{
				if (i > cellWidth / 2)
				{
					adjList[std::make_pair(i, j)].push_back(std::make_pair(i - cellWidth, j));
				}
				if (i < WIDTH - (cellWidth + 1))
				{
					adjList[std::make_pair(i, j)].push_back(std::make_pair(i + cellWidth, j));
				}
				if (j > cellWidth / 2)
				{
					adjList[std::make_pair(i, j)].push_back(std::make_pair(i, j - cellWidth));
				}
				if (j < -(cellWidth + 1))
				{
					adjList[std::make_pair(i, j)].push_back(std::make_pair(i, j + cellWidth));
				}
				centerList.push_back(make_pair(i, j));
			}
		}
	}
	for (int i = 0; i < centerList.size(); i++)
	{
		for (int j = centerList[i].second - (cellWidth / 2 - 1); j < centerList[i].second + (cellWidth / 2); j++)
		{
			for (int k = centerList[i].first - (cellWidth / 2 - 1); k < centerList[i].first + (cellWidth / 2); k++)
			{
				if (i % 3 == 0)
				{
					grid[k][j] = 19;
				}
				else if (i % 3 == 1)
				{
					grid[k][j] = 20;
				}
				else if (i % 3 == 2)
				{
					grid[k][j] = 21;
				}
			}
		}
	}
	
	for (int i = 0; i < centerList.size(); i++)
	{
			cells.emplace_back(centerList[i].first, centerList[i].second);
	}
	for(int i = 0; i < cells.size(); i++){
		cells[i].setPixels(cells[i].center.first, cells[i].center.second, cellWidth);
	}
	vector<pair<int, int>> cellPixels;
	for(int i = 0; i < cells.size(); i++){
		cellPixels = cells[i].getPixels();
		for(int j = 0; j < cellPixels.size(); j++){
			if(i % 3 == 0){
			grid[cellPixels[j].first][cellPixels[j].second] = 25;
			}else if(i % 3 == 1){
			grid[cellPixels[j].first][cellPixels[j].second] = 26;
			}else if(i % 3 == 2){
			grid[cellPixels[j].first][cellPixels[j].second] = 27;
			}
		}
	}
	
}

// Displays the initial grid
void Maze::draw_grid()
{
	for (size_t i = 0; i < WIDTH; ++i)
	{
		for (size_t j = 0; j < HEIGHT; ++j)
		{
			if (grid[i][j] == 1)
			{
				SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255); // Set draw color to purple
				SDL_RenderDrawPoint(renderer, i, j);				// Draw pixel at given coordinates
			}
		}
	}
	SDL_RenderPresent(renderer); // Show updated render
}

void Maze::draw_path_solver()
{
	for (size_t i = 0; i < WIDTH; i++)
	{
		for (size_t j = 0; j < HEIGHT; j++)
		{
			if (grid[i][j] == 25)
			{
				SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Set draw color to turquoise
				SDL_RenderDrawPoint(renderer, i, j);
			}
			if (grid[i][j] == 26)
			{
				SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Set draw color to turquoise
				SDL_RenderDrawPoint(renderer, i, j);
			}
			if (grid[i][j] == 27)
			{
				SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Set draw color to turquoise
				SDL_RenderDrawPoint(renderer, i, j);
			}
			if (grid[i][j] == 4)
			{
				SDL_SetRenderDrawColor(renderer, 0, 204, 0, 255); // Set draw color to turquoise
				SDL_RenderDrawPoint(renderer, i, j);
			}
			if (grid[i][j] == 5)
			{
				SDL_SetRenderDrawColor(renderer, 255, 128, 0, 255); // Set draw color to turquoise
				SDL_RenderDrawPoint(renderer, i, j);
			}
		}
	}
	SDL_RenderPresent(renderer);
}

// Testing purposes only
// Displays the contents of the graph by printing the adjacency list
void Maze::print_graph()
{
	for (auto i = adjList.begin(); i != adjList.end(); ++i)
	{
		std::cout << "(" << (*i).first.first << ", " << (*i).first.second << ")"
				  << " => ";
		std::vector<std::pair<int, int>> edges = (*i).second;
		for (size_t i = 0; i < edges.size(); ++i)
		{
			std::cout << "(" << edges[i].first << ", " << edges[i].second << ")";
		}
		std::cout << std::endl;
	}
}
/*
struct cell{
	int weight;
	pair<int, int> center;
	vector<pair<int, int>> pixels;
	priority_queue<cell*, vector<cell*>, greater<cell*>> neighbors;
	cell();
	cell(int x, int y);
	int getWeight();
	pair<int, int> getCenter();
	void setPixels(int topLeftX, int topLeftY, int cellPixelSize);
	void setNeigbor();
	cell* getNeighbor();
};

cell::cell();

cell::cell(int x, int y){
	center.first = x;
	center.second = y;
}

int cell::getWeight(){
	return this->weight;
}

pair<int, int> cell::getCenter(){
	return this->center;
}

void cell::setPixels(int topLeftX, int topLeftY, int cellPixelSize){
	for(int i = 0; i < cellPixelSize; i++){
		for(int j = 0; j < cellPixelSize; j++){
			this->pixels.push_back(make_pair(j + topLeftX, i + topLeftY));
		}
	}
}

int main(){
	int height = 1000;
	int width = 1000;
	int cellSize = cellWidth;

	for(int i = 0; i < height; i+cellWidth){
		for(int j = 0; )
	}
}

*/
