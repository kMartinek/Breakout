#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "paddle.h"
#include "graphics.h"


Paddle::Paddle() {}

Paddle::Paddle(float p_x, float p_y, const char* texturePath, Graphics& graphics)
	:x(p_x), y(p_y)
{
	height = 20;
	width = 80;
	tex = graphics.loadTexture(texturePath);
	sourceRect.x = 0;
	sourceRect.y = 0;
	sourceRect.w = 480;
	sourceRect.h = 276;
	
}

void Paddle::update(int new_x)
{
	if (new_x >= 800 - 80) x = 720;
	else x = new_x;

	
}
//mislim da je nepotrebno od tud
SDL_Texture* Paddle::getTexture()
{
	return tex;
}

//probably nepotrebno
SDL_Rect Paddle::getSourceRect()
{
	return sourceRect;
}

float Paddle::getX()
{
	return x;
}

float Paddle::getY()
{
	return y;
}

int Paddle::getWidth()
{
	return width;
}

int Paddle::getHeight()
{
	return height;
}

void Paddle::draw(Graphics& graphics)
{
	SDL_Rect destRect = { int(x), int(y), width, height };
	graphics.render(tex, &sourceRect, &destRect);
}

bool Paddle::CollisionL()
{
	return lastFrameCollisionL;
}

bool Paddle::CollisionR()
{
	return lastFrameCollisionR;
}