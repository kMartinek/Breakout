#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "graphics.h"

class Brick
{

private:
	float x, y;
	int height, width;
	int hitPoints, hitPointsCurrent;
	std::string type;
	int score;
	bool visible;
	SDL_Texture* tex;
	SDL_Texture* crack1;
	SDL_Texture* crack2;
	


public:
	Brick();
	Brick(float p_x, float p_y, std::string brick_type, int score, int hp, std::string textPath, Graphics& graphics, int height, int width); //dodati kasnije tip
	void update();
	SDL_Texture* getTexture();

	float getX();
	float getY();
	int getHeight();
	int getWidth();
	bool loseHP();
	bool isVisible();
	void draw(Graphics& graphics);

	std::string getType();
	int getScore();

};