#include "maze.h"
#include <iostream>
#include <cstdlib>
#include<unistd.h>
//#include <dos.h>


Maze::Maze(int n) {
	this->size = n;
	//Open SDL
	SDL_Init(SDL_INIT_VIDEO);
	//Create window and renderer
	SDL_CreateWindowAndRenderer(n+500, n+200, 0, &window, &renderer);
	//Make renderer black
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	//These function calls are for testing only
	build_grid(); //done
	//print_graph();
	adjMat_Builder(); //done
	rand_prims(realAdjMat, realAdjMat.size());

	


	//Hold screen until exit
	while (quit == false) {
		if (SDL_PollEvent(&event) && event.type == SDL_QUIT) {
			quit = true;
			break;
		}
	}

	//Upon quit, clean up SDL resources
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}


//Traverses SDL window region pixel by pixel. Creates a grid where each cell
//is 10x10 pixels. The center pixel of each cell is treated as a vertex
//in a graph and an edge between every neighbor vertex is inserted into
//the adjacency list
void Maze::build_grid() {
	int cellSize = size/10;

	//makes the walls
	for(int i =0; i <= size; i++){
		vector<int> tmp;
		for(int j = 0; j <= size; j++){
			if (i % 10 == 0 || j % 10 == 0) {
				tmp.push_back(1);
			}
			else {
				tmp.push_back(0);
			}
		}
		grid.push_back(tmp);
	}
	

	//draws the grid and makes adjMatrix
	for (int i = 0; i < grid.size() ; ++i) {
		vector<int> tmp;
		for (int j = 0; j < grid[i].size(); ++j) {
			if (grid[i][j] == 1) {
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);		//Set draw color to white
				SDL_RenderDrawPoint(renderer, i, j);			//Draw pixel at given coordinates
			}
			if(i < 10 && j < 10 && grid[i][j] !=1){
				SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);		//Set draw color to green
				SDL_RenderDrawPoint(renderer, i, j);			//Draw pixel at given coordinates
			}
			if(i > size-10 && j > size-10 && grid[i][j] !=1 && i < size && j <size){
				SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);		//Set draw color to red
				SDL_RenderDrawPoint(renderer, i, j);			//Draw pixel at given coordinates
			}

			if(i % 5 == 0 && j % 5 == 0 && grid[i][j] != 1){
				
				pair<int, int> p(i,j);
				edges.push_back(p);
				//weights.push_back((rand()%20) +1);
				tmp.push_back((rand()%20) +1);
			}
		}
		if(tmp.size() != 0){
			adjMat.push_back(tmp);
		}
	}
	SDL_RenderPresent(renderer);		//Show updated render

}


void Maze::adjMat_Builder(){
	int maxSize = adjMat.size()*adjMat.size();
	//cout <<adjMat.size() << " " << maxSize << endl;

	for(int i = 0; i < maxSize; i++){
		vector<int> tmp; 
		for(int j = 0; j < maxSize; j++){
			int check =0;
			//up
			if(i>= adjMat.size()){
				if(j == i-adjMat.size()){
					check =1;
					int row = j/adjMat.size();
					int col = j%adjMat.size();
					tmp.push_back(adjMat[row][col]);
				}
			}
			
			//down
			if(i < maxSize-adjMat.size()){
				if(j == i+adjMat.size()){
					check =1;					
					int row = j/adjMat.size();
					int col = j%adjMat.size();
					tmp.push_back(adjMat[row][col]);
				}
			}

			//right
			if((i+1)%adjMat.size() != 0){
				if(j == i+1){
					check =1;
					int row = j/adjMat.size();
					int col = j%adjMat.size();
					tmp.push_back(adjMat[row][col]);
				}
			}

			if((i+1)%adjMat.size() != 1){
				if(j == i-1){
					check =1;
					int row = j/adjMat.size();
					int col = j%adjMat.size();
					tmp.push_back(adjMat[row][col]);
				}
			}

			if(check ==0){
				tmp.push_back(1000);
			}
		}
		realAdjMat.push_back(tmp);
		
	}
}


void Maze::rand_prims(vector<vector<int>> adj, int vert){
	    //used to store the new graph with lowest weight
    int newGraph[vert];
    
    int key[vert];
    
 	bool setChecker[vert];
    // Initialize all keys as and setchecker to false
    for (int i = 0; i < vert; i++){
        key[i] = 99999, setChecker[i] = false;
    }
 

    key[0] = 0;
   

    newGraph[0] = -1;

    for (int count = 0; count < vert - 1; count++) {
         
     
     int mintmp = 9999999;
     int index;
       //finds the lowest index and also sets the setChecker at that index true to signal that its been added
       for (int v = 0; v < adj.size(); v++){
          if (setChecker[v] == false && key[v] < mintmp){
            mintmp = key[v];
            index = v;
          }
        }
        
        setChecker[index] = true;

        for (int w = 0; w < vert; w++){
 
            if (adj[index][w] && setChecker[w] == false && adj[index][w] < key[w]){
                newGraph[w] = index;
                key[w] = adj[index][w];
            }

		}
    }


	gen_maze(newGraph, vert);
}


void Maze::gen_maze(int mazeLayout[],int vert){
	cout << size /10 << endl;
	for(int i =1; i < vert; i++){
		int a = i;
		int b = mazeLayout[i];
		if(a > b){
			int tmp = b;
			b = a;
			a = tmp;
		}

		
		//right and left
		if(a+1 == b){
			
			int j = edges[a].second+5;
			int k = edges[a].first-4;
			for(int l = 0; l < 9; l++){
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);		//Set draw color to green
				SDL_RenderDrawPoint(renderer, j, k);			//Draw pixel at given coordinates
				k++;
			}
			SDL_RenderPresent(renderer);
			//unsigned int microsecond = 1000000;
			usleep(5000);
		}

		//up and down
		else if(a+(size/10) == b){
			int j = edges[a].second-4;
			int k = edges[a].first+5;

			for(int l =0; l < 9; l++){
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);		//Set draw color to green
				SDL_RenderDrawPoint(renderer, j, k);			//Draw pixel at given coordinates
				j++;
			}
			SDL_RenderPresent(renderer);
			//unsigned int microsecond = 1000000;
			usleep(5000);
		}



		

		

	}
}


//Testing purposes only
//Displays the contents of the graph by printing the adjacency list
void Maze::print_graph() {
	for(int i = 0; i < edges.size(); i++){
		cout << edges[i].first << " " << edges[i].second << endl;
	}

}