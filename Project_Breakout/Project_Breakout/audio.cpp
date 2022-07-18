#include "audio.h"

Audio::Audio()
{
	
	if (!Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT , 2, 4096))
	{
		std::cout << "Failed to load: "<< Mix_GetError;
		exit(-1);
	};
}


Mix_Chunk* Audio::loadAudio(const char* filePath)
{
	Mix_Chunk* sound = NULL;
	if (soundEffects.count(filePath) == 0)
	{
		soundEffects[filePath] = Mix_LoadWAV(filePath);
	}

	if (soundEffects[filePath] == NULL)
	{
		std::cout << "Failed to load audio: " << SDL_GetError << std::endl;
	}

	return soundEffects[filePath];
}

	
void Audio::playSoundEffect(std::string path)
{
	Mix_PlayChannel(-1, soundEffects[path], 0);
}