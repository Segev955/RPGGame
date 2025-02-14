#include "Map.h"
#include "Game.h"
#include <fstream>

Map::Map() {
}

Map::~Map() {
}

void Map::LoadMap(std::string path, int xSize, int ySize) {
	char c;
	std::fstream mapFile;
	mapFile.open(path);

	int srcX, srcY;

	for (int y = 0; y < ySize; y++) {
		for (int x = 0; x < xSize; x++) {
			mapFile.get(c);
			srcY = atoi(&c) * 32;
			mapFile.get(c);
			srcX = atoi(&c) * 32;
			Game::AddTile(srcX, srcY, x * 64, y * 64);
			mapFile.ignore();
		}
	}
	mapFile.close();
}