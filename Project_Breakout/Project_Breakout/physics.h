

#pragma once


#include "ball.h"
#include "player.h"
#include "level.h"





bool collisionCheckPaddle(Ball& ball, Paddle& paddle, float& back);
bool collisionCheckWall(Ball& ball);
bool collisionCheckFloor(Ball& ball);
bool collisionCheckBrick(Ball& ball, Brick& brick, float& back);

float pointDistance(vec2f p1, vec2f p2);

vec2f closestPoint(vec2f ball, Brick& brick);

vec2f closestPoint(vec2f ball, Paddle& paddle);


void newDirection(Ball& ball, Brick& brick);

void newDirectionPaddle(Ball& ball, Paddle& paddle);

//bool update(Ball& ball, Paddle& paddle, std::vector<Brick>& bricks, Player& player, Level& level);

