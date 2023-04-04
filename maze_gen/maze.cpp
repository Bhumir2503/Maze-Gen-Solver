#include "maze.h"
#include <iostream>

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
			if (i % 100 == 0 || j % 100 == 0)
			{
				grid[i][j] = 1;
			}
			// else if((i % 100 >= 40 && i % 100 <= 60 )||(j % 100 >= 40 && j % 100 <= 60 )){
			//	grid[i][j] = 2; //have a 3 pixel path in each cell in the 4th pixel row
			// }
			else if (i % 100 >= 40 && i % 100 <= 60 && j % 100 >= 40 && j % 100 <= 60)
			{
				grid[i][j] = 100;
			}
			else if ((i % 100 >= 40 && i % 100 <= 60) && (j % 100 <= 50))
			{ // up
				grid[i][j] = 2;
			}
			else if ((i % 100 >= 40 && i % 100 <= 60) && (j % 100 >= 50))
			{ // down
				grid[i][j] = 3;
			}
			else if ((i % 100 <= 40) && (j % 100 >= 40 && j % 100 <= 60))
			{ // left
				grid[i][j] = 4;
			}
			else if ((i % 100 >= 60) && (j % 100 >= 40 && j % 100 <= 60))
			{ // left
				grid[i][j] = 5;
			}
			else
			{
				grid[i][j] = 0;
			}

			// This condition only passes for pixels in the center of each cell
			if (i % 50 == 0 && i % 100 != 0 && j % 50 == 0 && j % 100 != 0)
			{
				if (i > 5)
				{
					adjList[std::make_pair(i, j)].push_back(std::make_pair(i - 100, j));
				}
				if (i < WIDTH - 15)
				{
					adjList[std::make_pair(i, j)].push_back(std::make_pair(i + 100, j));
				}
				if (j > 5)
				{
					adjList[std::make_pair(i, j)].push_back(std::make_pair(i, j - 100));
				}
				if (j < HEIGHT - 15)
				{
					adjList[std::make_pair(i, j)].push_back(std::make_pair(i, j + 100));
				}
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
			if (grid[i][j] == 2)
			{
				SDL_SetRenderDrawColor(renderer, 85, 246, 187, 255); // Set draw color to turquoise
				SDL_RenderDrawPoint(renderer, i, j);
			}
			if (grid[i][j] == 100)
			{
				SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Set draw color to turquoise
				SDL_RenderDrawPoint(renderer, i, j);
			}
			if (grid[i][j] == 3)
			{
				SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Set draw color to turquoise
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
