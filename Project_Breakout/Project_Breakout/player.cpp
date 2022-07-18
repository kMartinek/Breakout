#include "player.h"

Player::Player()
{
	level = 1;
	score = 0;
	lives = 3;
	bricksDestroyed = 0;
}

void Player::reset()
{
	level = 1;
	score = 0;
	lives = 3;
	bricksDestroyed = 0;
}

int Player::getScore()
{
	return score;
}

int Player::getLives()
{
	return lives;
}

int Player::getLevel()
{
	return level;
}

int Player::getBricks()
{
	return bricksDestroyed;
}

void Player::levelUp()
{
	++level;
}

void Player::loseLife()
{
	--lives;
}

void Player::brickDestroyed(int points)
{	
	score+=points;
	++bricksDestroyed;
}

void Player::setBricks(int bricks)
{
	bricksDestroyed = bricks;
}