#include "cell.h"
#include <vector>
#include <queue>
cell::cell(){

}

cell::cell(int x, int y, int i){
	index = i;
	center.first = x;
	center.second = y;
	weight = 20;
}

int cell::getWeight(){
	return this->weight;
}

pair<int, int> cell::getCenter(){
	return this->center;
}

void cell::setPixels(int centerX, int centerY, int cellPixelSize){
	for(int i = centerY-(cellPixelSize/2 -1); i < centerY+(cellPixelSize/2); i++){
		for(int j = centerX-(cellPixelSize/2 -1); j < centerX+(cellPixelSize/2); j++){
			this->pixels.push_back(make_pair(j, i));
		}
	}
}

void cell::setNeigbor(int width, int height, cell neighborCell){
	
}

cell cell::getNeighbor(){
  //  cell n = neighbors.top().second;
  //  neighbors.pop();
  //  return n;
}



vector<pair<int, int>> cell::getPixels(){
    return this->pixels;
}

