#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "graphics.h"

class Paddle
{
private:
	float x, y;
	int height, width;

	SDL_Texture* tex;
	SDL_Rect sourceRect;



public:
	Paddle();
	Paddle(float p_x, float p_y, const char* textPath, Graphics& graphics);
	void update(int new_x);
	SDL_Texture* getTexture();
	SDL_Rect getSourceRect();
	float getX();
	float getY();
	int getHeight();
	int getWidth();

	bool CollisionL();
	bool CollisionR();

	bool lastFrameCollisionL;
	bool lastFrameCollisionR;

	void draw(Graphics& graphics);
};