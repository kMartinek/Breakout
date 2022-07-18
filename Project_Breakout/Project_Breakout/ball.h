#pragma once

#include <SDL.h>
#include <SDL_image.h>
//#include <vector>
#include "graphics.h"
//#include "brick.h"
#include "paddle.h"
#include "vec2f.h"


class Ball
{
private:
	vec2f position;
	vec2f direction;
	float x, y;
	float height, width;
	float radius;
	SDL_Texture* tex;
	SDL_Rect sourceRect;
	float direction_x, direction_y;
	float velocity;


public:
	Ball();
	Ball(float p_x, float p_y, const char* textPath, Graphics& graphics);
	
	//void update();
	void onPaddle(Paddle& paddle);
	
	SDL_Texture* getTexture();
	SDL_Rect getSourceRect();
	
	
	float getX();
	float getY();
	float getCenterX();
	float getCenterY();
	
	void draw(Graphics& graphics);
	//void collisionCheck(Paddle& paddle);
	//void collisionCheck(Brick& brick);
	
	
	void start(int level);
	int getVelocity();
	float getRadius();
	vec2f getPosition();
	vec2f getCenter();
	vec2f getDirection();
	void setPosition(float x, float y);
	void setDirection(float x, float y);
	void setVelocity(int vel);
	

};