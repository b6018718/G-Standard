#include <iostream>
#include <stdio.h>
#include <sstream>
#include <stdlib.h>
#include <cstdlib>
#include <time.h>
#include <ctime>
#include <math.h>
#include <vector>
#include <SDL.h>
#include "sdl_mixer.h"
#include "SDL_TTF.h"
#include "SDL_image.h"
#include "SDL_gamecontroller.h"
#include "Game.h"

//Count Lines OF Code = ctrl + shift + f
//^(?!(\s*\*))(?!(\s*\-\-\>))(?!(\s*\<\!\-\-))(?!(\s*\n))(?!(\s*\*\/))(?!(\s*\/\*))(?!(\s*\/\/\/))(?!(\s*\/\/))(?!(\s*\}))(?!(\s*\{))(?!(\s(using))).*$
using namespace std;

int main(int argc, char* args[])
{
	#ifdef _DEBUG
		// _CrtSetBreakAlloc(2007);
		_onexit(_CrtDumpMemoryLeaks);
	#endif

	srand(time(NULL));
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		cout << "SDL initialization failed. SDL Error: " << SDL_GetError();
	else
		cout << "SDL initialization succeeded!";

	Game* gStandard = new Game();
	delete gStandard;
	Mix_CloseAudio();
	IMG_Quit();
	SDL_Quit();
	cin.get();
	return 0;
}