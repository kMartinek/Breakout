#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "brick.h"

Brick::Brick(){ }


Brick::Brick(float p_x, float p_y, std::string brick_type, int points, int hp, std::string textPath, Graphics& graphics, int hght, int wdth)
	:x(p_x), y(p_y), score(points), height(hght), width(wdth), hitPoints(hp)
{
	
	
	hitPointsCurrent = hitPoints;


	visible = true;

	tex = graphics.loadTexture(textPath.c_str());

	crack1 = graphics.loadTexture("crack1.png");


	crack2 = graphics.loadTexture("crack2.png");

	
	

}

void Brick::update()
{
	if (hitPointsCurrent == 0) visible = false;
}

SDL_Texture* Brick::getTexture()
{
	return tex;
}


float Brick::getX()
{
	return x;
}

float Brick::getY()
{
	return y;
}

int Brick::getWidth()
{
	return width;
}

int Brick::getHeight()
{
	return height;
}

void Brick::draw(Graphics& graphics)
{
	if (visible==true)
	{
		SDL_Rect destRect = { int(x), int(y), width, height };
		graphics.render(tex, NULL, &destRect);

		if (hitPointsCurrent == 1 && hitPoints > 0 && hitPointsCurrent!=hitPoints)
		{
			graphics.render(crack1, NULL, &destRect);
			graphics.render(crack2, NULL, &destRect);
		}
		if (hitPointsCurrent == 2 && hitPoints > 0 && hitPointsCurrent != hitPoints)
		{
			graphics.render(crack1, NULL, &destRect);
			
		}

	}
	
}

bool Brick::isVisible()
{
	return visible;
}

// loseHP, returns true if brick was  destroyed
bool Brick::loseHP()
{
	hitPointsCurrent -= 1;
	if (hitPointsCurrent == 0)
		return true;
	else
		return false;

}

std::string Brick::getType()
{
	return type;
}

int Brick::getScore()
{
	return score;
}