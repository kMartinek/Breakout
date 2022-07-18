#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "game.h"
#include "brick_type.h"
#define PI 3.14159265359


namespace
{
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;
	const int windowWidth = 800;
	const int windowHeight = 600;

}

Game::Game()


{
	//SDL initialization
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "SDL_Init failed. SDL_ERROR: " << SDL_GetError() << std::endl;

	//SDL_image initialization
	if (!(IMG_Init(IMG_INIT_PNG)))
		std::cout << "IMG_Init failed. SDL_ERROR: " << SDL_GetError() << std::endl;

	if (SDL_Init(SDL_INIT_AUDIO) < 0)
	{
		std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() <<std::endl;
		
	}
	
	// sve inicijalizacije
	Graphics graphics1("Breakout", 800, 600);
	graphics = graphics1;

	////audio = audio1;
	gameLoop();
}

Game::~Game()
{

}

void Game::gameLoop()
{
	
	//Input input;
	
	SDL_Event event;

	//initialization xml
	//Ball ball(/*.....*/);

	





	// HUD  0 - 50
	// brick area 50 - 400 
	
	//initialization for FPS cap
	int frameStart = SDL_GetTicks();
	int frameTime;


	
	//game objects
	Player player;
	Level level;

	Paddle paddle1(10, 550, "white_brick.png", graphics);
	paddle = paddle1;

	Ball ball1((paddle.getX() + paddle.getWidth() / 2), 530, "earth.png", graphics);
	ball = ball1;
	std::vector <Brick> bricks;

	//game flags
	bool gameRunning = true;
	bool newGame = true;
	bool playStarted = false;
	bool victory = false;
	bool levelLoaded = false;
	bool gameOver = false;
	bool startPlay = false;


	//main menu screen






	// game
	while (gameRunning)
	{	
		frameStart = SDL_GetTicks();

		while (SDL_PollEvent(&event))
		{

			//check for events and resolve them
			if (event.type == SDL_QUIT)
				gameRunning = false;

			if (event.type == SDL_MOUSEMOTION)
			{
				paddle.update(event.motion.x);
			}
			
			if (event.type == SDL_MOUSEBUTTONDOWN)
			{		
				std::cout << "click \n";
				startPlay = true;
			}

		}

		

		if (newGame)
		{
			//setup new game
			player.reset();
			startPlay = false;
			levelLoaded = false;
			playStarted = false;
			gameOver = false;
			victory = false;
			newGame = false;
		}

		if (!levelLoaded)
		{
			//load new level
			level = Level("level" + std::to_string(player.getLevel()) + ".xml", graphics);
			level.load(bricks, graphics);
			levelLoaded = true;
			//treba postat player.brickCount
			player.setBricks(0);
		}

	
		
		if (!playStarted)
		{
			
			//fixes ball on the paddle and waits for click to start it 
			ball.onPaddle(paddle);
			if (startPlay)
			{
				ball.start(player.getLevel());
				playStarted = true;
				startPlay = false;
			}
			
		}
		else
		{

			//resolveCollisions
			
			if (!update(ball, paddle, bricks, player, level))
			{	
				std::cout << "tu sam";
				if (player.getLives() == 0) gameOver = true;
				ball.setVelocity(0);
				playStarted = false;
			}
		}
		

	
		

		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
			
		//draws everything on window
		draw(graphics, bricks);


		//end of level check
		if (level.brickCount == player.getBricks())
		{
			levelLoaded = false;
			playStarted = false;
			startPlay = false;
			bricks.clear();
			player.levelUp();
			if (player.getLevel() > 2) victory = true;
		}

		//victory check
		if (victory)
		{
			//nekakav victory screen message umjesto ovog
			gameRunning = false;
		}
		
		//game Over check
		if (gameOver)
		{
			//game over screen message umjesto ovog
			gameRunning = false;
		}
	}


	//gamepause

	//highscore

}

	


bool Game::update(Ball& ball, Paddle& paddle, std::vector<Brick>& bricks, Player& player, Level& level)
{
	//Spliting to multiple checks to avoid ball spawning in bricks
	
	
	float velocitySplit = ball.getVelocity();

	int timesChecked = 1;


	while (velocitySplit > ball.getRadius())
	{
		++timesChecked;
		velocitySplit = ball.getVelocity() / timesChecked;
	}

	vec2f closPnt;

	int i;

	float back;

	for (i = 0; i < timesChecked; ++i)
	{
		ball.setPosition(ball.getPosition().x + velocitySplit * ball.getDirection().x, ball.getPosition().y + velocitySplit * ball.getDirection().y);


		if (collisionCheckFloor(ball))
		{
			//play sound
			player.loseLife();
			return false;
		}

		if (collisionCheckWall(ball))
		{
			//play sound
		}

		//bricks check
		for (std::vector<Brick>::iterator it = bricks.begin(); it != bricks.end(); ++it)
		{
			if (it->isVisible())
			{
				if (collisionCheckBrick(ball, *it, back))
				{
					//calculate new angle
					
					
					std::cout << "Ball.getPosition x: " << ball.getPosition().x << "\n";
					std::cout << "Ball.getPosition y; " << ball.getPosition().y << "\n";



					newDirection(ball, *it);

					ball.setPosition(
						ball.getPosition().x + back * ball.getDirection().x,
						ball.getPosition().y + back * ball.getDirection().y
					);


					std::cout << "new Ball.getPosition x: " << ball.getPosition().x << "\n";
					std::cout << "new Ball.getPosition y; " << ball.getPosition().y << "\n";
					
					

					if (it->loseHP())
					{
						player.brickDestroyed(it->getScore());
						//play sound 

						it->update();
					}
				}
			}
		}


		if (collisionCheckPaddle(ball, paddle, back))
		{
			//play sound
			newDirectionPaddle(ball, paddle);
		}
		else
		{
			paddle.lastFrameCollisionL = false;
			paddle.lastFrameCollisionR = false;
		}
	}
	return true;
}

	








	/*
	for (std::vector<Brick>::iterator it = bricks.begin(); it != bricks.end(); ++it)
	{
		std::cout << "Try check: \n";
		ball.collisionCheck(*it);
	}
	
	std::cout << "Try check: \n";
	ball.collisionCheck(paddle);
	ball.update();

	*/



void Game::draw(Graphics& graphics, std::vector<Brick>& bricks)
{
	graphics.clear();
	//drawBackground();
	/*
	
	bricks.draw(graphics);
	hud.draw(graphics)

	*/

	
	for (std::vector<Brick>::iterator it = bricks.begin(); it != bricks.end(); ++it)
		it->draw(graphics);
	paddle.draw(graphics);
	ball.draw(graphics);
	graphics.display();
}


/*

vec2f Game::closestPoint(vec2f ball, Brick& brick)
{
	vec2f closestPoint;
	if (ball.x <= brick.getX())
		closestPoint.x = brick.getX();
	else if (ball.x >= brick.getX() + brick.getWidth())
		closestPoint.x = brick.getX() + brick.getWidth();
	else
		closestPoint.x = ball.x;

	if (ball.y <= brick.getY())
		closestPoint.y = brick.getY();
	else if (ball.y >= brick.getY() + brick.getHeight())
		closestPoint.y = brick.getY() + brick.getHeight();
	else
		closestPoint.y = ball.y;

	return closestPoint;
}


vec2f Game::closestPoint(vec2f ball, Paddle& brick)
{
	vec2f closestPoint;
	if (ball.x <= brick.getX())
		closestPoint.x = brick.getX();
	else if (ball.x >= brick.getX() + brick.getWidth())
		closestPoint.x = brick.getX() + brick.getWidth();
	else
		closestPoint.x = ball.x;

	if (ball.y <= brick.getY())
		closestPoint.y = brick.getY();
	else if (ball.y >= brick.getY() + brick.getHeight())
		closestPoint.y = brick.getY() + brick.getHeight();
	else
		closestPoint.y = ball.y;

	return closestPoint;
}

float Game::pointDistance(vec2f p1, vec2f p2)
{
	return sqrtf(powf(p1.x - p2.x, 2) + powf(p1.y - p2.y, 2));
}


//checks if there was a collision and sets the ball on the collision point
bool Game::collisionCheckBrick(Ball& ball, Brick& brick, float& back)
{
	vec2f clPoint = closestPoint(ball.getCenter(), brick);
	if (pointDistance(ball.getCenter(), clPoint) < ball.getRadius())
	{
		back = ball.getRadius() - pointDistance(ball.getCenter(), clPoint);
		ball.setPosition(
			(ball.getPosition().x - back * ball.getDirection().x)
			,
			(ball.getPosition().y - back * ball.getDirection().y)
		);
		return true;
	}
	else
		return false;

}

bool Game::collisionCheckPaddle(Ball& ball, Paddle& brick, float& back)
{
	vec2f clPoint = closestPoint(ball.getCenter(), brick);
	if (pointDistance(ball.getCenter(), clPoint) < ball.getRadius())
	{
		back = ball.getRadius() - pointDistance(ball.getCenter(), clPoint);
		ball.setPosition(
			(ball.getPosition().x - back * ball.getDirection().x)
			,
			(ball.getPosition().y - back * ball.getDirection().y)
		);
		return true;
	}
	else
		return false;
}



void Game::newDirection(Ball& ball, Brick& brick)
{
	vec2f clPoint = closestPoint(ball.getCenter(), brick);

	if (((clPoint.x == brick.getX()) && (clPoint.y == brick.getY()))
		|| ((clPoint.x == brick.getX()) && (clPoint.y == (brick.getY() + brick.getHeight())))
		|| ((clPoint.x == (brick.getX() + brick.getWidth())) && (clPoint.y == brick.getY()))
		|| ((clPoint.x == (brick.getX() + brick.getWidth())) && (clPoint.y == (brick.getY() + brick.getHeight()))))
	{

		//corner collision
		float line_coef = (clPoint.y - ball.getPosition().y) / (clPoint.x - ball.getPosition().x);
		float normal_coef = -1 / line_coef;
		float normal_angle = atan(normal_coef) * (180 / PI);


		float new_angle;
		float mirror;

		//top left corner
		if ((clPoint.x == brick.getX()) && (clPoint.y == brick.getY()))
		{

			normal_angle += 180;
			mirror = normal_angle + 90;
			new_angle = 2 * mirror - ball.getDirection().angle_deg() + 180;

		}

		//bottom left corner
		else if ((clPoint.x == brick.getX()) && (clPoint.y == brick.getY() + brick.getHeight()))
		{
			mirror = normal_angle + 90;
			new_angle = 2 * mirror - ball.getDirection().angle_deg() + 180;
		}

		//bottom right corner
		else if ((clPoint.x == brick.getX() + brick.getWidth()) && (clPoint.y == brick.getY() + brick.getHeight()))
		{
			normal_angle += 360;
			mirror = normal_angle + 90;
			new_angle = 2 * mirror - ball.getDirection().angle_deg() - 180;
		}
		//upper right corner
		else
		{

			normal_angle += 180;
			mirror = normal_angle + 90;
			new_angle = 2 * mirror - ball.getDirection().angle_deg() + 180;
		}

		while (new_angle > 360) new_angle -= 360;

		//avoiding too parallel angles which would slow down the game a lot
		if (new_angle > 175 && new_angle < 185)
		{
			if (new_angle > 180) new_angle = 185;
			else new_angle = 175;
		}
		else if (new_angle > 355) new_angle = 355;
		else if (new_angle < 5) new_angle = 5;


		float angle_rad = new_angle * (PI / 180);
		ball.setDirection(vec2f(cos(angle_rad), sin(angle_rad)));

	}

	else if (clPoint.y == brick.getY() || clPoint.y == brick.getY() + brick.getHeight())
	{
		ball.setDirection(vec2f(ball.getDirection().x, ball.getDirection().y * (-1)));
		//top collision
	}

	else
	{
		//side collision
		ball.setDirection(vec2f(ball.getDirection().x * (-1), ball.getDirection().y));
	}


}


bool Game::collisionCheckFloor(Ball& ball)
{
	if (ball.getPosition().y + ball.getDirection().y >= 600)
		return true;
	else
		return false;
}



bool Game::collisionCheckWall(Ball& ball)
{
	bool collision = false;
	if (ball.getPosition().x + ball.getDirection().x <= 0)
	{
		ball.setDirection(vec2f(ball.getDirection().x * (-1), ball.getDirection().y));
		ball.setPosition(0, ball.getPosition().y);
		collision = true;
	}
	else if (ball.getPosition().x + ball.getDirection().x >= 800 - 2 * ball.getRadius())
	{
		ball.setDirection(vec2f(ball.getDirection().x * (-1), ball.getDirection().y));
		ball.setPosition(800 - 2 * ball.getRadius(), ball.getPosition().y);
		collision = true;

	}


	if (ball.getPosition().y + ball.getDirection().y <= 0)
	{
		ball.setDirection(vec2f(ball.getDirection().x, ball.getDirection().y * (-1)));
		ball.setPosition(ball.getPosition().x, 0);
		collision = true;
	}

	return collision;

}



void Game::newDirectionPaddle(Ball& ball, Paddle& paddle)
{
	vec2f clPoint = closestPoint(ball.getCenter(), paddle);

	if (clPoint.y == paddle.getY())
	{
		float ratioHit = 1 - (clPoint.x - paddle.getX()) / paddle.getWidth();
		float angle_deg = 30 + ratioHit * 120;

		float angle_rad = angle_deg * (PI / 180);

		ball.setDirection(vec2f(cos(angle_rad), sin(angle_rad)));
	}


	else //side collision
		ball.setDirection(vec2f(ball.getDirection().x * (-1), ball.getDirection().y));

}
*/