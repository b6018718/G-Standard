#pragma once
#include "Music.h"
#include "Fonts.h"
#include "Screen.h"
#include "SDL_ttf.h"
class Game
{
public:
	Game();
	~Game();

	Music music;
	Fonts fonts;
	Screen screen;

	void GameLoop();
	void CloseGame();
};

