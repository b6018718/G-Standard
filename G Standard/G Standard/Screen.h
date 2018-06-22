#pragma once
#include <SDL.h>
#include "SDL_image.h"
#include <iostream>
#include <list>
#include <algorithm>

struct FormattedTexture
{
	std::shared_ptr <SDL_Texture> textureData;
	std::string fileName;
};

class Screen
{
public:
	Screen();
	~Screen();

	void loadMedia(std::weak_ptr <SDL_Texture>& loadTexture, std::string filename);
	std::weak_ptr <SDL_Texture> newTexture(std::string filename);
	void closeWindow();
	void deleteTexture(std::weak_ptr <SDL_Texture>& textureToDelete);

	void clear();
	void blit(std::weak_ptr <SDL_Texture> weakBlitTexture, int sourceX, int sourceY, int sourceW, int sourceH, int destinationX, int destinationY);
	void blit(std::weak_ptr <SDL_Texture> weakBlitTexture, int destinationX, int destinationY);
	void update();

private:
	std::weak_ptr <SDL_Texture> generateTexture(std::string filename);
	SDL_Window * window;
	std::list <FormattedTexture> textureList;
	SDL_Renderer * renderer;
};

