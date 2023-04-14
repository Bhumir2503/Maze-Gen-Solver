#include "maze.h"
#include <iostream>
#include <cstdlib>
#include<unistd.h>
#include <random>
//#include <dos.h>


Maze::Maze() {
	//this->size = n;
	//Open SDL
	SDL_Init(SDL_INIT_VIDEO);
	//Create window and renderer
	SDL_CreateWindowAndRenderer(1500, 1200, 0, &window, &renderer);
	//Make renderer black
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);	
	
	


	//These function calls are for testing only
	repeat();
	


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

void Maze::repeat(){
	grid.clear();
	edges.clear();
	weights.clear();
	adjMat.clear();
	realAdjMat.clear();
	blackWindow();
	button_builder();
	build_grid(); //done
	adjMat_Builder(); //done
	rand_prims(realAdjMat, realAdjMat.size()); //done
}


void:: Maze::blackWindow(){
	for(int i = 0; i < 1001; i++){
		for(int j = 0; j < 1001; j++){
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);		//Set draw color to green
			SDL_RenderDrawPoint(renderer, i, j);			//Draw pixel at given coordinates
		}
	}
	SDL_RenderPresent(renderer);
}
void Maze::button_builder(){
	for(int i = 0; i < 200; i++){
		for(int j = 0; j < 100; j++){
			SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);		//Set draw color to green
			SDL_RenderDrawPoint(renderer, i+50, j+1050);			//Draw pixel at given coordinates
		}

		for(int j = 0; j < 100; j++){
			SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);		//Set draw color to green
			SDL_RenderDrawPoint(renderer, i+350, j+1050);			//Draw pixel at given coordinates
		}

		for(int j = 0; j < 100; j++){
			SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);		//Set draw color to green
			SDL_RenderDrawPoint(renderer, i+650, j+1050);			//Draw pixel at given coordinates
		}

		for(int j = 0; j < 100; j++){
			SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);		//Set draw color to green
			SDL_RenderDrawPoint(renderer, i+950, j+1050);			//Draw pixel at given coordinates
		}

		for(int j = 0; j < 100; j++){
			SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);		//Set draw color to green
			SDL_RenderDrawPoint(renderer, i+1250, j+1050);			//Draw pixel at given coordinates
		}
	}

	//5*5
	
	for(int i =0 ; i <50; i++){
		for(int j =0; j<5; j++){
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);		//Set draw color to green
			SDL_RenderDrawPoint(renderer, i+125, j+1075);			//Draw pixel at given coordinates
		}
	}

	for(int i =0 ; i <50; i++){
		for(int j =0; j<5; j++){
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);		//Set draw color to green
			SDL_RenderDrawPoint(renderer, i+125, j+1100);			//Draw pixel at given coordinates
		}
	}

	for(int i =0 ; i <50; i++){
		for(int j =0; j<5; j++){
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);		//Set draw color to green
			SDL_RenderDrawPoint(renderer, i+125, j+1125);			//Draw pixel at given coordinates
		}
	}

	for(int i = 0; i< 25; i++){
		for(int j = 0; j <5; j++){
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);		//Set draw color to green
			SDL_RenderDrawPoint(renderer, 125+j, 1080+i);			//Draw pixel at given coordinates
		}
	}

	for(int i = 0; i< 25; i++){
		for(int j = 0; j <5; j++){
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);		//Set draw color to green
			SDL_RenderDrawPoint(renderer, 170+j, 1105+i);			//Draw pixel at given coordinates
		}
	}



	//10*10

	//20*20

	//50*50

	//100*100

	SDL_RenderPresent(renderer);

	bool notClicked = true;
	while(notClicked){
		if(SDL_PollEvent(&event) &&event.type == SDL_MOUSEBUTTONDOWN){
			if(event.button.button == SDL_BUTTON_LEFT ){
				int x,y;
				SDL_GetMouseState(&x,&y);
				if(y >= 1050 && y <=1150 ){
					if(x>50 &&x<250){
						size = 50;
						cell = 1000/(size/10);
						notClicked = false;
					}

					if(x>350 &&x<550){
						size = 100;
						cell = 1000/(size/10);
						notClicked = false;
					}

					if(x>650 &&x<850){
						size = 200;
						cell = 1000/(size/10);
						notClicked = false;
					}

					if(x>950 &&x<1150){
						size = 500;
						cell = 1000/(size/10);
						notClicked = false;
					}

					if(x>1250 &&x<1450){
						size = 1000;
						cell = 1000/(size/10);
						notClicked = false;
					}

				}
			}
		}

	}










}


//Traverses SDL window region pixel by pixel. Creates a grid where each cell
//is 10x10 pixels. The center pixel of each cell is treated as a vertex
//in a graph and an edge between every neighbor vertex is inserted into
//the adjacency list
void Maze::build_grid() {
	//makes the walls
	for(int i =0; i <= 1000; i++){
		vector<int> tmp;
		for(int j = 0; j <= 1000; j++){
			if (i % cell == 0 || j % cell == 0) {
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
			if(i < cell && j < cell && grid[i][j] !=1){
				SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);		//Set draw color to green
				SDL_RenderDrawPoint(renderer, i, j);			//Draw pixel at given coordinates
			}
			if(i > 1000-cell && j > 1000-cell && grid[i][j] !=1 && i < 1000 && j <1000){
				SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);		//Set draw color to red
				SDL_RenderDrawPoint(renderer, i, j);			//Draw pixel at given coordinates
			}

			if(i % (cell/2) == 0 && j % (cell/2) == 0 && grid[i][j] != 1){
				
				pair<int, int> p(i,j);
				edges.push_back(p);
			    std::random_device dev;
        		std::mt19937 rng(dev());
        		std::uniform_int_distribution<std::mt19937::result_type> dist20(1,20); // distribution in range [0, 5]

				tmp.push_back(dist20(rng));
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
	
	for(int i =1; i < vert; i++){
		int a = i;
		int b = mazeLayout[i];
		//cout << a<< " "<< b<< endl;
		if(a > b){
			int tmp = b;
			b = a;
			a = tmp;
		}

		
		//right and left
		if(a+1 == b){
			
			int j = edges[a].second+(cell/2);
			int k = edges[a].first-(cell/2)+1;
			for(int l = 0; l < (cell-1); l++){
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);		//Set draw color to green
				SDL_RenderDrawPoint(renderer, j, k);			//Draw pixel at given coordinates
				k++;
			}
			SDL_RenderPresent(renderer);
			usleep(5000000/(10*size));
		}

		//up and down
		else if(a+(size/10) == b){
			int j = edges[a].second-(cell/2)+1;
			int k = edges[a].first+(cell/2);

			for(int l =0; l < (cell-1); l++){
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);		//Set draw color to green
				SDL_RenderDrawPoint(renderer, j, k);			//Draw pixel at given coordinates
				j++;
			}
			SDL_RenderPresent(renderer);
			usleep(5000000/(10*size));
		}
	}





	bool notClicked = true;
	while(notClicked){
		int x,y;
		SDL_GetMouseState(&x,&y);
		if (SDL_PollEvent(&event) && event.type == SDL_QUIT) {
			notClicked = false;
			break;
		}
		if(SDL_PollEvent(&event) &&event.type == SDL_MOUSEBUTTONDOWN){
				if(y >= 1050 && y <=1150 ){
					if(x>50 &&x<250){
						repeat();
					}

					if(x>350 &&x<550){
						repeat();
					}

					if(x>650 &&x<850){
						repeat();
					}

					if(x>950 &&x<1150){
						repeat();
					}

					if(x>1250 &&x<1450){
						repeat();
					}

				}
				else{
					notClicked = false;
					quit = true;
					SDL_DestroyRenderer(renderer);
					SDL_DestroyWindow(window);
					SDL_Quit();
				}
			
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