#include "Screen.h"

using namespace std;

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

Screen::Screen()
{
	window = NULL;
	renderer = NULL;
	
	//Initialise SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());

	//Initialise window
	window = SDL_CreateWindow("G Standard", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL)
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
	else
	{
		//Initialise PNG loading
		int imgFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imgFlags) & imgFlags))
		{
			printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		}
	}

	//Initialise Renderer
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (renderer == NULL)
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
	//Initialise renderer color
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
}

Screen::~Screen()
{
}

void Screen::loadMedia(std::weak_ptr <SDL_Texture>& loadTexture,std::string filename)
{
	bool loaded(false);
	std::weak_ptr <SDL_Texture> tempWeakTexture = loadTexture;
	std::shared_ptr <SDL_Texture> tempSharedTexture = tempWeakTexture.lock();
	bool found(false);
	//Iterator
	std::list <FormattedTexture>::iterator deleteTexture = textureList.begin();
	while (!found && deleteTexture != textureList.end())
	{
		if (deleteTexture->fileName == filename)	//Texture already in cache
		{
			loadTexture = deleteTexture->textureData;
			loaded = true;
			found = true;
		}
		else
		{
			if (tempSharedTexture == deleteTexture->textureData)	//Overwrite texture
			{
				SDL_DestroyTexture(deleteTexture->textureData.get());
				textureList.erase(deleteTexture);
				found = true;
			}
		}
		if (!found)
			deleteTexture++;
	}
	//Load Texture not in cache
	tempSharedTexture.reset();
	tempWeakTexture.reset();
	if (!loaded)
	{
		loadTexture.reset();
		loadTexture = generateTexture(filename);
	}
}

std::weak_ptr<SDL_Texture> Screen::generateTexture(std::string filename)
{
	/*struct FormattedTexture
	{
		std::shared_ptr <SDL_Texture> textureData;
		std::string fileName;
	};*/

	//Initalise surface
	SDL_Surface* loadedSurface = IMG_Load(filename.c_str());
	if (loadedSurface == nullptr)
		printf("Unable to load image %s! SDL_image Error: %s\n", filename.c_str(), IMG_GetError());
	else
	{
		//Initalise Texture
		textureList.push_back({ std::shared_ptr <SDL_Texture>(SDL_CreateTextureFromSurface(renderer, loadedSurface)) , filename }); //Struct initalisation
		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}
	return textureList.back().textureData;
}

std::weak_ptr<SDL_Texture> Screen::newTexture(std::string filename)
{
	return generateTexture(filename);
}



void Screen::closeWindow()
{
	//Destroy Textures
	for (auto deleteTexture : textureList)
	{
		SDL_DestroyTexture(deleteTexture.textureData.get());
	}
	textureList.clear();
	
	//Destroy Renderer
	SDL_DestroyRenderer(renderer);

	//Destroy Window
	SDL_DestroyWindow(window);
	
}

void Screen::deleteTexture(std::weak_ptr<SDL_Texture>& textureToDelete)
{
	//Iterator
	bool found(false);
	std::weak_ptr <SDL_Texture> tempWeakTexture = textureToDelete;
	std::shared_ptr <SDL_Texture> tempSharedTexture = tempWeakTexture.lock();
	std::list <FormattedTexture>::iterator deleteTexture = textureList.begin();
	while (!found && deleteTexture != textureList.end())
	{
		if (tempSharedTexture == deleteTexture->textureData)	//Overwrite texture
		{
			SDL_DestroyTexture(deleteTexture->textureData.get());
			textureList.erase(deleteTexture);
			found = true;
		}
		if (!found)
			deleteTexture++;
	}
	tempSharedTexture.reset();
	tempWeakTexture.reset();
}

void Screen::clear()
{
	//Clear screen
	SDL_RenderClear(renderer);
}

void Screen::blit(std::weak_ptr<SDL_Texture> weakBlitTexture, int sourceX, int sourceY, int sourceW, int sourceH, int destinationX, int destinationY)
{
	std::weak_ptr <SDL_Texture> tempWeakTexture = weakBlitTexture;
	std::shared_ptr <SDL_Texture> tempSharedTexture = tempWeakTexture.lock();
	SDL_Rect destination { destinationX, destinationY };
	if (sourceX != -1 && sourceY != -1 && sourceW != -1 && sourceH != -1)
	{
		SDL_Rect source { sourceX, sourceY, sourceW, sourceH };
		//Render texture to screen
		SDL_RenderCopy(renderer, tempSharedTexture.get(), &source, &destination);
	}
	else
	{
		SDL_RenderCopy(renderer, tempSharedTexture.get(), NULL, &destination);
	}

	tempSharedTexture.reset();
	tempWeakTexture.reset();
}

void Screen::blit(std::weak_ptr<SDL_Texture> weakBlitTexture, int destinationX, int destinationY)
{
	blit(weakBlitTexture, -1, -1, -1, -1, destinationX, destinationY);
}

void Screen::update()
{
	//Update screen
	SDL_RenderPresent(renderer);
}

