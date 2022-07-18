#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include <map>
#include <iostream>
#include <string>

class Audio
{
private:
	std::map<std::string, Mix_Chunk* > soundEffects;

public:
	Audio();
	Mix_Chunk* loadAudio(const char* path);
	void playSoundEffect(std::string path);
};