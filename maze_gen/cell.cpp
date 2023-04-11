#include "cell.h"
#include <vector>
#include <queue>
cell::cell(){

}

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

void cell::setPixels(int centerX, int centerY, int cellPixelSize){
	for(int i = centerY-(cellPixelSize/2 -1); i < centerY+(cellPixelSize/2); i++){
		for(int j = centerX-(cellPixelSize/2 -1); j < centerX+(cellPixelSize/2); j++){
			this->pixels.push_back(make_pair(j, i));
		}
	}
}
cell* cell::getNeighbor(){
    cell* n = this->neighbors.top();
    this->neighbors.pop();
    return n;
}
vector<pair<int, int>> cell::getPixels(){
    return this->pixels;
}

