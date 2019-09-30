#include "Game.h"

//Controller Constants
const int JOYSTICK_DEAD_ZONE = 8000;

Game::Game()
{
	//Initalise Fonts Class
	if (TTF_Init() == -1) {
		printf("TTF_Init: %s\n", TTF_GetError());
		exit(2);
	}

	//Initalise Controller Support
	SDL_Joystick* gGameController = NULL;
	SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS, "1");

	GameLoop();
	CloseGame();
}

Game::~Game()
{
}

void Game::GameLoop()
{
	//While application is running
	bool quit(false);
	SDL_Event gameEvent;
	screen.clear();
	while (!quit){
		//Handle events on queue
		while (SDL_PollEvent(&gameEvent) != 0){
			//User requests quit
			if (gameEvent.type == SDL_QUIT){
				quit = true;
			}
			// Example: How to use graphics
			if (!loaded) {
				screen.blit(graphics.waddleDee, 100, 100);
				loaded = true;
			}
			// Check for screen resizing events
			screen.handleEvent(gameEvent);
			// Display the screen
			screen.update();

		}
	}
}

void Game::CloseGame()
{
	screen.closeWindow();
	music.FreeSounds();
	fonts.FreeFonts();
}
