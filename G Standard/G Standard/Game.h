#pragma once
#include "Music.h"
#include "Fonts.h"
#include "Screen.h"
#include "SDL_ttf.h"
#include "Graphics.h"
class Game
{
public:
	Game();
	~Game();

	Music music;
	Fonts fonts;
	Screen screen;
	Graphics graphics;

	bool loaded = false;

	void GameLoop();
	void CloseGame();
};

