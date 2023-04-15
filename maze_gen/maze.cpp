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
	Sizebutton_builder();
	if(!quit){
		repeat();
	}


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


void Maze::reset(){
	grid.clear();
	edges.clear();
	weights.clear();
	adjMat.clear();
	realAdjMat.clear();
	blackWindow();//done
	Sizebutton_builder(); //done
	build_grid(); //done
	adjMat_Builder(); //done
	rand_prims(realAdjMat, realAdjMat.size()); //done
}


void Maze::repeat(){
	grid.clear();
	edges.clear();
	weights.clear();
	adjMat.clear();
	realAdjMat.clear();
	blackWindow();//done
	build_grid(); //done
	adjMat_Builder(); //done
	rand_prims(realAdjMat, realAdjMat.size()); //done
	//gen_maze //done
}


void:: Maze::blackWindow(){
	for(int i = 0; i < 1500; i++){
		for(int j = 0; j < 1001; j++){
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);		
			SDL_RenderDrawPoint(renderer, i, j);			
		}
	}
	SDL_RenderPresent(renderer);
}


int Maze::Sizebutton_builder(){
	for(int i = 0; i < 200; i++){

		//5
		for(int j = 0; j < 100; j++){
			SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);		
			SDL_RenderDrawPoint(renderer, i+50, j+1050);			
		}

		//10
		for(int j = 0; j < 100; j++){
			SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);		
			SDL_RenderDrawPoint(renderer, i+350, j+1050);			
		}

		//25
		for(int j = 0; j < 100; j++){
			SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);		
			SDL_RenderDrawPoint(renderer, i+650, j+1050);			
		}

		//50
		for(int j = 0; j < 100; j++){
			SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);		
			SDL_RenderDrawPoint(renderer, i+950, j+1050);			
		}

		//100
		for(int j = 0; j < 100; j++){
			SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);		
			SDL_RenderDrawPoint(renderer, i+1250, j+1050);			
		}
	}

	
	for(int j = 0; j < 100; j++){
		//exit 
		for(int i = 0; i < 140; i++){
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);		
			SDL_RenderDrawPoint(renderer, i+1100, j+100);	
		}
	}
	

	//5*5
	
	for(int i =0 ; i <50; i++){
		for(int j =0; j<5; j++){
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);		
			SDL_RenderDrawPoint(renderer, i+125, j+1075);			
		}
	}

	for(int i =0 ; i <50; i++){
		for(int j =0; j<5; j++){
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);		
			SDL_RenderDrawPoint(renderer, i+125, j+1100);			
		}
	}

	for(int i =0 ; i <50; i++){
		for(int j =0; j<5; j++){
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);		
			SDL_RenderDrawPoint(renderer, i+125, j+1125);			
		}
	}

	for(int i = 0; i< 25; i++){
		for(int j = 0; j <5; j++){
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);		
			SDL_RenderDrawPoint(renderer, 125+j, 1080+i);			
		}
	}

	for(int i = 0; i< 25; i++){
		for(int j = 0; j <5; j++){
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);		
			SDL_RenderDrawPoint(renderer, 170+j, 1105+i);			
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
				if(y >=100 && y <=200){
					//exit
					if(x>=1100 && x<= 1240){
					notClicked = false;
					quit = true;
					return 0;
					}
				}
			}
		}

	}










}


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
				SDL_RenderDrawPoint(renderer, i, j);			
			}
			if(i < cell && j < cell && grid[i][j] !=1){
				SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);		
				SDL_RenderDrawPoint(renderer, i, j);			
			}
			if(i > 1000-cell && j > 1000-cell && grid[i][j] !=1 && i < 1000 && j <1000){
				SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);		//Set draw color to red
				SDL_RenderDrawPoint(renderer, i, j);			
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


int Maze::gen_maze(int mazeLayout[],int vert){
	
	for(int i =1; i < vert; i++){
		int a = i;
		int b = mazeLayout[i];

		realAdjMat[a][b] =50;
		realAdjMat[b][a] = 50;

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
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);		
				SDL_RenderDrawPoint(renderer, j, k);
				grid[j][k] = 0;			
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
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);		
				SDL_RenderDrawPoint(renderer, j, k);			
				grid[j][k] =0;
				j++;
			}
			SDL_RenderPresent(renderer);
			usleep(5000000/(10*size));
		}
	}

	for(int j = 0; j < 100; j++){
		//exit and reset
		for(int i = 0; i < 140; i++){
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);		
			SDL_RenderDrawPoint(renderer, i+1100, j+100);			
			//SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);		
			//SDL_RenderDrawPoint(renderer, i+1260, j+100);			
		}

		//BFS
		for(int i =0; i < 300; i++){
			SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);		
			SDL_RenderDrawPoint(renderer, i+1100, j+325);			
		}

		//DFS
		for(int i =0; i < 300; i++){
			SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);		
			SDL_RenderDrawPoint(renderer, i+1100, j+550);			
		}
		
		//Djikstra's
		for(int i =0; i < 300; i++){
			SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);		
			SDL_RenderDrawPoint(renderer, i+1100, j+775);			
		}

	}



	SDL_RenderPresent(renderer);
	for(int i = 0; i < realAdjMat.size(); i++){
		for(int j = 0; j < realAdjMat.size(); j++){
			if(realAdjMat[i][j] != 50){
				realAdjMat[i][j] = 0;
			}
			else{
				realAdjMat[i][j] =1;
			}
		}
	}




	bool notClicked = true;
	while(notClicked){
		int x,y;
		
		if(SDL_PollEvent(&event) &&event.type == SDL_MOUSEBUTTONDOWN){
			SDL_GetMouseState(&x,&y);
				if(y >= 1050 && y <=1150 ){
					if(x>50 &&x<250){
						size = 50;
						cell = 1000/(size/10);
						notClicked = false;
						repeat();
					}

					if(x>350 &&x<550){
						size = 100;
						cell = 1000/(size/10);
						notClicked = false;
						repeat();
					}

					if(x>650 &&x<850){
						size = 250;
						cell = 1000/(size/10);
						notClicked = false;
						repeat();
					}

					if(x>950 &&x<1150){
						size =500;
						cell = 1000/(size/10);
						notClicked = false;
						repeat();
					}

					if(x>1250 &&x<1450){
						size = 1000;
						cell = 1000/(size/10);
						notClicked = false;
						repeat();
					}

				}
				if(y >=100 && y <=200){
					//exit
					if(x>=1100 && x<= 1240){
					notClicked = false;
					quit = true;
					return 0;
					}
					if(x>=1260 && x <=1400){
						notClicked = false;
						visited = vector<bool>(realAdjMat.size(), false);
						DFS(0);
						cout << pathway.size() << endl;
						for(int k = 0; k < pathway.size(); k++){
							for(int i = 0; i < cell; i++){
								int a = edges[pathway[k]].second-(cell/2);
								int b = edges[pathway[k]].first- (cell/2);
								for(int j = 0; j < cell; j++){
									if(grid[i+a][j+b] != 1){
										SDL_SetRenderDrawColor(renderer, 0, 150, 0, 255);		//Set draw color to white
										SDL_RenderDrawPoint(renderer, i+a, j+b);
									}
								}
								SDL_RenderPresent(renderer);
							}
						}
					}
				}
			
		}

	}


}


int Maze::DFS(int start){
	// Print the current node
	int check = 0;
    cout << start << " " << endl;
	int a = edges[start].second;
	int b = edges[start].first;
	a = a-(cell/2);
	b = b-(cell/2);
	
	for(int i = 0; i < cell; i++){
		for(int j = 0; j < cell; j++){
			if(grid[i+a][j+b] != 1){
				SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);		//Set draw color to white
				SDL_RenderDrawPoint(renderer, i+a, j+b);
			}
		}
	}
	
	

	SDL_RenderPresent(renderer);
	usleep(5000000/(10*size));
	
	if(start == realAdjMat.size()-1){
		pathway.push_back(start);
		return -1;
	}

    // Set current node as visited
    visited[start] = true;
 
    // For every node of the graph
    for (int i = 0; i < realAdjMat[start].size(); i++) {
 
        // If some node is adjacent to the current node
        // and it has not already been visited
        if (realAdjMat[start][i] == 1 && (!visited[i])) {
            check = DFS(i);
			if(check == -1){
				pathway.push_back(start);
				return -1;
			}
        }
    }
}

