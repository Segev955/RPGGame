#pragma once
#include <string>

class Map {

private:


public:
	Map();
	~Map();

	static void LoadMap(std::string path, int xSize, int ySize);

};