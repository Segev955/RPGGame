#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "Components.h"
#include "Vector2D.h"
#include "Collision.h"


Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

SDL_Rect Game::camera = { 0,0,800,640 };

std::vector<ColliderComponent*> Game::colliders;

bool Game::isRunning = false;

auto& player(manager.addEntity());

const char* mapFile = "assets/tilest.png";

enum groupLabels : std::size_t {
	groupMap,
	groupPlayers,
	groupColliders
};

auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));


Game::Game() {}

Game::~Game() {}


void Game::init(const char* title, int width, int height, bool fullscreen) {
	int flags = 0;
	if (fullscreen)
		flags = SDL_WINDOW_FULLSCREEN;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Subsystem init!" << std::endl;

		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		if(window) 
			std::cout << "Window created!" << std::endl;

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created!" << std::endl;
		}
		isRunning = true;
	}

	map = new Map();

	Map::LoadMap("assets/map2.map", 32, 32);

	player.addComponent<TransformComponent>(2);
	player.addComponent<SpriteComponent>("assets/player_anims.png", true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);
}

void Game::handleEvents() {

	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}

}

void Game::update() {
	manager.refresh();
	manager.update();

	camera.x = player.getComponent<TransformComponent>().position.x - 400;
	camera.y = player.getComponent<TransformComponent>().position.y - 320;

	if (camera.x < 0)
		camera.x = 0;
	if (camera.y < 0)
		camera.y = 0;
	if (camera.x > camera.w)
		camera.x = camera.w;
	if (camera.y > camera.h)
		camera.y = camera.h;

}



void Game::render() {
	SDL_RenderClear(renderer);
	for (auto& t : tiles) {
		t->draw();
	}
	for (auto& p : players) {
		p->draw();
	}

	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit;
	std::cout << "Game cleaned" << std::endl;
}

void Game::AddTile(int srcX, int srcY, int xpos, int ypos) {
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcX,srcY,xpos,ypos,mapFile);
	tile.addGroup(groupMap);
}