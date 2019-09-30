#pragma once
#include <SDL.h>
#include "SDL_image.h"
#include <iostream>
#include <sstream>
#include <list>
#include <algorithm>
#include <string>
#include <map>

using namespace std;

class Screen
{
public:
	Screen();
	~Screen();

	void handleEvent(SDL_Event& e);
	void toggleFullScreen();

	void closeWindow();
	map<string, SDL_Texture*>::iterator deleteTexture(string filename);
	void deleteAllTextures();

	void clear();
	void blit(string filename, int sourceX, int sourceY, int sourceW, int sourceH, int destinationX, int destinationY);
	void blit(string filename, int destinationX, int destinationY);
	void update();

	int getWidth();
	int getHeight();
	
	bool hasMouseFocus();
	bool hasKeyBoardFocus();
	bool isMinimised();

private:
	SDL_Window * window;
	map<string, SDL_Texture*> textures;
	SDL_Renderer * renderer;

	string windowName;
	bool debugMode;

	int windowHeight;
	int windowWidth;

	bool mouseFocus;
	bool keyboardFocus;
	bool fullScreen;
	bool minimised;
};

