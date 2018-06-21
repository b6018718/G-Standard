#include "Fonts.h"



Fonts::Fonts()
{
	//const char * fontName = "PressStart2P-Regular.ttf";

	/*
	font18 = TTF_OpenFont(fontName, 18);
	if (!font18)
		printf("TTF_OpenFont: %s\n", TTF_GetError());

	font20 = TTF_OpenFont(fontName, 20);
	if (!font20)
		printf("TTF_OpenFont: %s\n", TTF_GetError());

	font24 = TTF_OpenFont(fontName, 24);
	if (!font24) 
		printf("TTF_OpenFont: %s\n", TTF_GetError());

	font28 = TTF_OpenFont(fontName, 28);
	if (!font28)
		printf("TTF_OpenFont: %s\n", TTF_GetError());

	font48 = TTF_OpenFont(fontName, 48);
	if (!font48)
		printf("TTF_OpenFont: %s\n", TTF_GetError());
	*/
}

Fonts::~Fonts()
{
}

void Fonts::FreeFonts()
{
	TTF_CloseFont(font18);
	TTF_CloseFont(font20);
	TTF_CloseFont(font24);
	TTF_CloseFont(font28);
	TTF_CloseFont(font48);
}
