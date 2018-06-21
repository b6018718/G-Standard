#include "Music.h"
#include <vector>
#include <iostream>


Music::Music()
{
	//Initialise SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
	}

	/*
	song = Mix_LoadMUS("sound/battle.mp3");
	if (song == NULL)
		printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());

	soundEffect = Mix_LoadWAV("sound/hit.wav");
	if (soundEffect == NULL)
		printf("Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError());

	*/
}

Music::~Music()
{
}
/*
void Music::PlaySong()
{
	Mix_PlayMusic(song, -1);
}

void Music::PlaySoundEffect()
{
	Mix_PlayChannel(-1, soundEffect, 0);
}
*/

void Music::PauseMusic()
{
	Mix_PauseMusic();
}

void Music::ResumeMusic()
{
	Mix_ResumeMusic();
}

void Music::HaltMusic()
{
	Mix_HaltMusic();
}

void Music::FreeSounds()
{
	//Mix_FreeMusic(song);
	//Mix_FreeChunk(soundEffect);
}

void Music::SetVolume(float newVolume)  //Volume should be a number equal or between 0 and 10
{
	if (newVolume >= 0 && newVolume <= 10)
	{
		int intVol = (int)floor((newVolume / 10) * 128);
		Mix_VolumeMusic(intVol);
		Mix_Volume(-1, intVol);
		volume = newVolume;
	}
}