#pragma once
#include "SDL_ttf.h"
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <stdlib.h>
#include <string.h>
class Fonts
{
public:
	Fonts();
	~Fonts();

	TTF_Font* font18;
	TTF_Font* font20;
	TTF_Font* font24;
	TTF_Font* font28;
	TTF_Font* font48;

	SDL_Color foregroundColor = { 255, 255, 255 };
	SDL_Color backgroundColor = { 0, 0, 0 };

	void FreeFonts();
};

