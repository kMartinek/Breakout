#pragma once


class Player
{
private:
	int score;
	int level;
	int lives;
	int bricksDestroyed;

public:
	Player();
	void reset();
	int getScore();
	int getLives();
	int getLevel();
	int getBricks();

	void levelUp();
	void loseLife();
	void brickDestroyed(int points);
	void setBricks(int brick);

};