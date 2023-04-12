#include <queue>
#include <vector>
#include <iostream>
using namespace std;
struct cell{
	int index;
	int weight;
	pair<int, int> center;
	vector<pair<int, int>> pixels;
	priority_queue<pair<int, cell>, vector<pair<int, cell>>, greater<pair<int, cell>>> neighbors;
	cell();
	cell(int x, int y, int i);
	int getWeight();
	pair<int, int> getCenter();
	void setPixels(int centerX, int centerY, int cellPixelSize);
	void setNeigbor(int width, int height, cell neighborCell);
	cell getNeighbor();
    vector<pair<int, int>> getPixels();
    
};


