#include "Game.h"
#include "Music.h"
#include "SDL_ttf.h"

Game::Game()
{
	//Initalise Fonts Class
	if (TTF_Init() == -1) {
		printf("TTF_Init: %s\n", TTF_GetError());
		exit(2);
	}
}

Game::~Game()
{
}

void Game::GameLoop()
{
}
