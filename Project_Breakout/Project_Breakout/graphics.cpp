#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "graphics.h"


Graphics::Graphics() {};

Graphics::Graphics(const char* title, int screenWidth, int screenHeight)
	:window(NULL), renderer(NULL)
{
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);

	if (window == NULL)
	{
		std::cout << "Window failed to initialize. Error: " << SDL_GetError() << std::endl;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

Graphics::~Graphics()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}


void Graphics::render(SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect* dstRect)
{
	SDL_RenderCopy(renderer, texture, srcRect, dstRect);
}

void Graphics::display()
{
	SDL_RenderPresent(renderer);
}

void Graphics::clear()
{
	SDL_RenderClear(renderer);
}

SDL_Renderer* Graphics::getRenderer() const
{
	return renderer;
}

SDL_Texture* Graphics::loadTexture(const char* filePath)
{
	SDL_Texture* texture = NULL;
	if(textures.count(filePath)==0)
	{
		textures[filePath] = IMG_LoadTexture(renderer, filePath);
	}


	if (textures[filePath] == NULL)
		std::cout << "Failed to load image: " << SDL_GetError << std::endl;

	return textures[filePath];
}