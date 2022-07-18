#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "graphics.h"
#include "paddle.h"
#include "ball.h"
#include "level.h"
#include "player.h"
#include "physics.h"
#include "audio.h"

class Game
{
private:
	Paddle paddle;
	Ball ball;
	Graphics graphics;
	//Audio audio;

	
public:
	Game();
	~Game();
	
	void gameLoop();
	void draw(Graphics& graphics, std::vector<Brick>& bricks);
	bool update(Ball& ball, Paddle& paddle, std::vector<Brick>& bricks, Player& player, Level& level);
	/*
	bool collisionCheckPaddle(Ball& ball, Paddle& paddle, float& back);
	bool collisionCheckWall(Ball& ball);
	bool collisionCheckFloor(Ball& ball);
	bool collisionCheckBrick(Ball& ball, Brick& brick, float& back);

	float pointDistance(vec2f p1, vec2f p2);

	vec2f closestPoint(vec2f ball, Brick& brick);

	vec2f closestPoint(vec2f ball, Paddle& paddle);


	void newDirection(Ball& ball, Brick& brick);

	void newDirectionPaddle(Ball& ball, Paddle& paddle);
	*/
};