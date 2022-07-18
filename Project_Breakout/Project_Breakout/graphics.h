#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <map>

class Graphics
{
private:
	SDL_Window* window;
	SDL_Renderer* renderer;

	std::map<std::string, SDL_Texture*> textures;


public:
	Graphics();
	Graphics(const char* title, int screenWidth, int screenHeight);
	~Graphics();
	SDL_Texture* loadTexture(const char *filePath);
	void render(SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect* dstRect);
	void display();
	void clear();
	SDL_Renderer* getRenderer() const;


};