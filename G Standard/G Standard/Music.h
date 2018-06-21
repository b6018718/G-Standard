#pragma once
#include "SDL.h"
#include "sdl_mixer.h"
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <stdlib.h>
#include <ctime>
#include <math.h>
#include <vector>

using namespace std;

class Music
{
public:
	Music();
	~Music();

	int volume = 5;

	//void PlaySong();
	//void PlaySoundEffect();

	void PauseMusic();
	void ResumeMusic();
	void HaltMusic();
	void FreeSounds();
	void SetVolume(float volume);

private:
	//Mix_Music * song;

	//Mix_Chunk * soundEffect;
};



