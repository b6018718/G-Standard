#include "Screen.h"

using namespace std;

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

Screen::Screen()
{
	window = NULL;
	renderer = NULL;

	windowHeight = 0;
	windowWidth = 0;

	mouseFocus = NULL;
	keyboardFocus = NULL;
	fullScreen = NULL;
	minimised = NULL;

	windowName = "G Standard";
	debugMode = false;
	
	
	//Initialise SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	
	
	//Initialise window
	window = SDL_CreateWindow("G Standard", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (window == NULL)
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
	else
	{
		// Initialise screen variables
		mouseFocus = true;
		keyboardFocus = true;
		windowHeight = SCREEN_HEIGHT;
		windowWidth = SCREEN_WIDTH;

		//Initialise PNG loading
		int imgFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imgFlags) & imgFlags))
		{
			printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		}
	}
	
	//Initialise Renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);


	if (renderer == NULL)
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
	//Initialise renderer color
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}

Screen::~Screen()
{
}

void Screen::handleEvent(SDL_Event & e)
{
	//Window event occured
	if (e.type == SDL_WINDOWEVENT) {
		//Caption update flag
		bool updateCaption = false;
		switch (e.window.event) {
		// Event - Window size changed
		case SDL_WINDOWEVENT_SIZE_CHANGED:
			windowWidth = e.window.data1;
			windowHeight = e.window.data2;
			update();
			break;
		// Mouse enter window
		case SDL_WINDOWEVENT_ENTER:
			mouseFocus = true;
			updateCaption = true;
			break;
		// Mouse left window
		case SDL_WINDOWEVENT_LEAVE:
			mouseFocus = false;
			updateCaption = true;
			break;
		// Window has keyboard focus
		case SDL_WINDOWEVENT_FOCUS_GAINED:
			keyboardFocus = true;
			updateCaption = true;
			break;
		//Window lost keyboard focus
		case SDL_WINDOWEVENT_FOCUS_LOST:
			keyboardFocus = false;
			updateCaption = true;
			break;
		// Window minimised
		case SDL_WINDOWEVENT_MINIMIZED:
			minimised = true;
			break;
		// Window maximised
		case SDL_WINDOWEVENT_MAXIMIZED:
			minimised = false;
			break;
		// Window restored
		case SDL_WINDOWEVENT_RESTORED:
			minimised = false;
			break;
		}
		// Update window caption with new data
		if (updateCaption && debugMode) {
			std::stringstream caption;
			caption << windowName << " - MouseFocus:" << ((mouseFocus) ? "On" : "Off") << " KeyboardFocus:" << ((keyboardFocus) ? "On" : "Off");
			SDL_SetWindowTitle(window, caption.str().c_str());
		}
		
	}
}

void Screen::toggleFullScreen()
{
	if (!fullScreen) {
		// Go full screen
		SDL_SetWindowFullscreen(window, SDL_TRUE);
		fullScreen = true;
		minimised = false;
	} else {
		// Unfull screen
		SDL_SetWindowFullscreen(window, SDL_FALSE);
		minimised = false;
	}
}

void Screen::closeWindow()
{
	//Destroy Textures
	deleteAllTextures();
	
	//Destroy Renderer
	SDL_DestroyRenderer(renderer);

	//Destroy Window
	SDL_DestroyWindow(window);
	
}

void Screen::deleteAllTextures() {
	map<string, SDL_Texture*>::iterator it = textures.begin();
	while (it != textures.end()) {
		it = deleteTexture((*it).first);
	}
}

map<string, SDL_Texture*>::iterator Screen::deleteTexture(string filename)
{
	// Erase the texture
	SDL_DestroyTexture(textures[filename]);
	// Create an iterator for the textures map
	map<string, SDL_Texture*>::iterator it;
	it = textures.find(filename);
	// Delete from the map
	it = textures.erase(it);

	return it;
}

void Screen::clear()
{
	//Clear screen
	SDL_RenderClear(renderer);
}

void Screen::blit(string filename, int sourceX, int sourceY, int sourceW, int sourceH, int destinationX, int destinationY)
{
	SDL_Texture *textureToLoad = nullptr;
	int textureWidth, textureHeight;
	// Get the texture to load from the cache
	if (textures.find(filename) == textures.end()) {
		SDL_Surface *tempSurface = IMG_Load(filename.c_str());
		textureToLoad = SDL_CreateTextureFromSurface(renderer, tempSurface);
		SDL_FreeSurface(tempSurface);
		textures[filename] = textureToLoad;
	} else {
		textureToLoad = textures[filename];
	}
	// Blit the texture to the screen
	SDL_QueryTexture(textureToLoad, NULL, NULL, &textureWidth, &textureHeight);
	SDL_Rect destination { destinationX, destinationY, textureWidth, textureHeight };
	if (sourceX != -1 && sourceY != -1 && sourceW != -1 && sourceH != -1)
	{
		SDL_Rect source { sourceX, sourceY, sourceW, sourceH };
		//Render texture to screen
		SDL_RenderCopy(renderer, textureToLoad, &source, &destination);
	} else {
		SDL_RenderCopy(renderer, textureToLoad, NULL, &destination);
	}
	textureToLoad = nullptr;
}

void Screen::blit(string filename, int destinationX, int destinationY)
{
	blit(filename, -1, -1, -1, -1, destinationX, destinationY);
}

void Screen::update()
{
	//Update screen
	if(!minimised)
		SDL_RenderPresent(renderer);
}

int Screen::getWidth()
{
	return windowWidth;
}

int Screen::getHeight()
{
	return windowHeight;
}

bool Screen::hasMouseFocus()
{
	return mouseFocus;
}

bool Screen::hasKeyBoardFocus()
{
	return keyboardFocus;
}

bool Screen::isMinimised()
{
	return minimised;
}

