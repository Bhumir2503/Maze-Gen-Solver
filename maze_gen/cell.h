#include <queue>
#include <vector>
#include <iostream>
using namespace std;
struct cell{
	int weight;
	pair<int, int> center;
	vector<pair<int, int>> pixels;
	priority_queue<cell*, vector<cell*>, greater<cell*>> neighbors;
	cell();
	cell(int x, int y);
	int getWeight();
	pair<int, int> getCenter();
	void setPixels(int centerX, int centerY, int cellPixelSize);
	void setNeigbor();
	cell* getNeighbor();
    vector<pair<int, int>> getPixels();
    
};


