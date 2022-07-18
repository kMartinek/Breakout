#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "ball.h"
#include <vector>


#include "game.h"

int main(int argc, char* args[])
{
	Game game;
	return 0;
};

/*
int main(int argc, char* args[])
{	
	//SDL initialization
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
			std::cout << "SDL_Init failed. SDL_ERROR: " << SDL_GetError() << std::endl;
	
	//SDL_image initialization
	if (!(IMG_Init(IMG_INIT_PNG)))
		std::cout << "IMG_Init failed. SDL_ERROR: " << SDL_GetError() << std::endl;

	const int FPS = 60;
	const int frameDelay = 1000 / FPS;
	int frameTime;
	Uint32 frameStart;

	RenderWindow window("Breakout", 800, 600);

	bool gameRunning = true;

	SDL_Event event;
	SDL_Texture* earth = window.loadTexture("earth.png");
	SDL_Texture* paddle_tex = window.loadTexture("white_brick.png");
	SDL_Texture* brick = window.loadTexture("white_brick.png");
	int row = 3;
	int collumn = 5;
	std::vector <Brick> bricks;
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < collumn; ++j)
		{
			Brick b(10 +j*70 , 10+i*30, brick);
			bricks.push_back(b);
		}
	}
	Ball ball(0, 0, earth);
	Paddle paddle(0, 550, paddle_tex);
	int i;

	while (gameRunning)
	{
		frameStart = SDL_GetTicks();
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				gameRunning = false;
		}
		window.clear();
		window.render_ball(ball);
		window.render_paddle(paddle);
		for (i = 0; i < 15; ++i) window.render_brick(bricks[i]);
		window.display();
		ball.update();
		paddle.update();
		
		frameTime = SDL_GetTicks()-frameStart;
	
		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}


	return 0;
}

*/