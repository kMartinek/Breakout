#include "ball.h"
#include <iostream>
//#define PI 3.14159265359


Ball::Ball() {};

Ball::Ball(float p_x, float p_y, const char* texturePath, Graphics& graphics)
	:x(p_x), y(p_y)
{
	vec2f position(p_x, p_y);
	vec2f direction(0, -1);
	height = 15;
	width = 15;
	tex = graphics.loadTexture(texturePath);
	radius = width / 2;
	sourceRect.x = 0;
	sourceRect.y = 0;
	sourceRect.w = 256;
	sourceRect.h = 256;

	velocity = 0;


}

/*
void Ball::update()
{
	
	//edge of screen check and move
	if (x + direction_x <= 0)
	{
		direction_x *= -1;
		x = 0;
	}
	else if (x + direction_x >= 800 - width)
	{
		direction_x *= -1;
		x = 800 - width;
	}
	else
		x += direction_x * velocity;

	if (y + direction_y <= 0)
	{
		direction_y *= -1;
		y = 0;
	}
	else if (y + direction_y >= 600 - height)
	{
		direction_y *= -1;
		y = 600 - height;
	}
	else y += direction_y * velocity;


}
*/
void Ball::onPaddle(Paddle& paddle)
{
	position.x = (paddle.getX() + paddle.getWidth() / 2) - radius;
	position.y = paddle.getY() - height;
	x = (paddle.getX() + paddle.getWidth() / 2) - radius;
	y = paddle.getY() - height;
}

SDL_Texture* Ball::getTexture()
{
	return tex;
}

SDL_Rect Ball::getSourceRect()
{
	return sourceRect;
}

float Ball::getX()
{
	return x;
}

float Ball::getY()
{
	return y;
}

float Ball::getCenterX()
{
	return (x + radius);
}

float Ball::getCenterY()
{
	return (y + radius);
}

vec2f Ball::getPosition()
{
	return position;
}


vec2f Ball::getCenter()
{
	return vec2f(position.x + radius, position.y + radius);
}

vec2f Ball::getDirection()
{
	return direction;
}


void Ball::setDirection(float x, float y)
{
	direction.x = x;
	direction.y = y;
}

void Ball::start(int level)
{
	direction.x = 0;
	direction.y = -1;
	velocity = 3 + level;
}

int Ball::getVelocity()
{
	return velocity;
}

void Ball::setVelocity(int vel)
{
	velocity = vel;
}

void Ball::setPosition(float newX, float newY)
{
	position.x = newX;
	position.y = newY;

}


float Ball::getRadius()
{
	return radius;
}
void Ball::draw(Graphics& graphics)
{
	SDL_Rect destRect = { int(position.x), int(position.y), width, height };
	graphics.render(tex, &sourceRect, &destRect);
}
/*
void Ball::collisionCheck(Paddle& paddle)
{
	float closestPoint_x, closestPoint_y;
	float distance;
	bool collision;

	//finding point on the paddle that is closest to ball in the next frame
	if (getCenterX() <= paddle.getX())
		closestPoint_x = paddle.getX();
	else if (getCenterX() >= paddle.getX() + paddle.getWidth())
		closestPoint_x = paddle.getX() + paddle.getWidth();
	else
		closestPoint_x = getCenterX();

	if (getCenterY() <= paddle.getY())
		closestPoint_y = paddle.getY();
	else if (getCenterY() >= paddle.getY() + paddle.getHeight())
		closestPoint_y = paddle.getY() + paddle.getHeight();
	else
		closestPoint_y = getCenterY();

	
	//calculating distance between ball center and closest point; 
	distance = sqrtf(powf(getCenterX() - closestPoint_x, 2) + powf(getCenterY() - closestPoint_y, 2));

	if (distance < radius)
	{
		collision = true;

		//checking if it was top collision 
		if (closestPoint_y == paddle.getY())
		{
			float ratioHit = 1 - (closestPoint_x - paddle.getX()) / paddle.getWidth();
			float angle_deg = 30 + ratioHit * 120;

			float angle_rad = angle_deg * (PI / 180);

			direction_x = cos(angle_rad);
			direction_y = -sin(angle_rad);
		}
		else if (closestPoint_y == paddle.getY() + paddle.getHeight())
		{
			float ratioHit = 1 - (closestPoint_x - paddle.getX()) / paddle.getWidth();
			float angle_deg = 30 + ratioHit * 120;

			float angle_rad = angle_deg * (PI / 180);

			direction_x = cos(angle_rad);
			direction_y = sin(angle_rad);
		}

		else //side collision
			direction_x *= -1;

	}

}	

void Ball::collisionCheck(Brick& brick)
{
	float closestPoint_x, closestPoint_y;
	float distance;
	int i;
	float next_frame_x, next_frame_y, next_split_x, next_split_y;
	next_frame_x = getCenterX()+velocity*direction_x;
	next_frame_y = getCenterY()+velocity*direction_y;
	next_split_x = getCenterX();
	next_split_y = getCenterY();

	bool collision = false;
	float velocity_split = velocity;
	int times_checked = 1;
	while (velocity_split > radius)
	{
		++times_checked;
		velocity_split = velocity / times_checked;
		
	}

	for (i = 0; i < times_checked; ++i)
	{
		
		next_split_x += velocity_split * direction_x;
		next_split_y += velocity_split * direction_y;

	

		//finding point on the brick that is closest to ball
		if (next_split_x <= brick.getX())
			closestPoint_x = brick.getX();
		else if (next_split_x >= brick.getX() + brick.getWidth())
			closestPoint_x = brick.getX() + brick.getWidth();
		else
			closestPoint_x = next_split_x;

		if (next_split_y <= brick.getY())
			closestPoint_y = brick.getY();
		else if (next_split_y >= brick.getY() + brick.getHeight())
			closestPoint_y = brick.getY() + brick.getHeight();
		else
			closestPoint_y = next_split_y;

		//calculating distance between ball center and closest point; 
		distance = sqrtf(powf(next_split_x - closestPoint_x, 2) + powf(next_split_y - closestPoint_y, 2));

		if (distance < radius)
		{
			collision = true;
			break;
		}
	}
	if (collision == true)
	{
		float collisionP_x, collisionP_y;
		//finding collision point

		collisionP_x = next_split_x + (radius - distance) * (direction_x * (-1));
		collisionP_y = next_split_y + (radius - distance) * (direction_y * (-1));

		//closest point to collision point
		if (collisionP_x <= brick.getX())
			closestPoint_x = brick.getX();
		else if (collisionP_x >= brick.getX() + brick.getWidth())
			closestPoint_x = brick.getX() + brick.getWidth();
		else
			closestPoint_x = collisionP_x;

		if (collisionP_y <= brick.getY())
			closestPoint_y = brick.getY();
		else if (collisionP_y >= brick.getY() + brick.getHeight())
			closestPoint_y = brick.getY() + brick.getHeight();
		else
			closestPoint_y = collisionP_y;

		if (((closestPoint_x == brick.getX()) && (closestPoint_y == brick.getY()))
			|| ((closestPoint_x == brick.getX()) && (closestPoint_y == (brick.getY() + brick.getHeight())))
			|| ((closestPoint_x == (brick.getX() + brick.getWidth())) && (closestPoint_y == brick.getY()))
			|| ((closestPoint_x == (brick.getX() + brick.getWidth())) && (closestPoint_y == (brick.getY() + brick.getHeight()))))
		{

			//corner collision
			float line_coef = (closestPoint_y - collisionP_y) / (closestPoint_x - collisionP_x);
			float normal_coef = -1 / line_coef;
			float normal_angle = atan(normal_coef) * (180/PI);
			std::cout << "Brick pos: " << brick.getX() << ", " << brick.getY() << ", " << brick.getWidth() << ", " << brick.getHeight() << "\n";
			std::cout << "\nClosest point:" << closestPoint_x << " " << closestPoint_y << "\n";
			vec2f direction(direction_x, direction_y);
			std::cout << direction.angle_deg() << "\n";
			std::cout << direction.angle_rad() << "\n";

			std::cout << "Ball angle:" << direction.angle_deg();
			std::cout << "Normal angle:" << normal_angle << "\n";
			float new_angle;
			float mirror;
			//top left corner
			if ((closestPoint_x == brick.getX()) && (closestPoint_y == brick.getY()))
			{


				std::cout << "Top Left: \n";
				normal_angle += 180;
				std::cout << "Normal angle:" << normal_angle << "\n";
				mirror = normal_angle + 90;
				std::cout << "mirror:" << mirror << "\n";
				new_angle = 2 * mirror - direction.angle_deg()+180;
				std::cout << "new_angle:" << new_angle << "\n";

			}

			//bottom left corner
			else if ((closestPoint_x == brick.getX()) && (closestPoint_y == brick.getY() + brick.getHeight()))
			{
				std::cout << "Bottom Left: \n";
				std::cout << "Normal angle:" << normal_angle << "\n";
				mirror = normal_angle + 90;
				std::cout << "mirror:" << mirror << "\n";
				new_angle = 2 * mirror - direction.angle_deg()+180;
				std::cout << "new_angle:" << new_angle << "\n";
			}

			//bottom right corner
			else if ((closestPoint_x == brick.getX() + brick.getWidth()) && (closestPoint_y == brick.getY() + brick.getHeight()))
			{
				std::cout << "bottom right: \n";
				normal_angle += 360;
				std::cout << "Normal angle:" << normal_angle << "\n";
				mirror = normal_angle + 90;
				std::cout << "mirror:" << mirror << "\n";
				new_angle = 2 * mirror - direction.angle_deg() - 180;
				std::cout << "new_angle:" << new_angle << "\n";
			}
			//upper right corner
			else
			{
				std::cout << "Top right: \n";

				normal_angle += 180;
				std::cout << "Normal angle:" << normal_angle << "\n";
				mirror = normal_angle + 90;
				std::cout << "mirror:" << mirror << "\n";
				new_angle = 2 * mirror - direction.angle_deg()+180;
				std::cout << "new_angle:" << new_angle << "\n";
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

			std::cout << new_angle << "\n\n";
			float angle_rad = new_angle * (PI / 180);
			direction_x = cos(angle_rad);
			direction_y = sin(angle_rad);
		}

		else if (closestPoint_y == brick.getY() || closestPoint_y == brick.getY() + brick.getHeight())
		{
			//top collision
			direction_y *= -1;
		}

		else
		{
			//side collision
			direction_x *= -1;
		}

		if(brick.loseHP()) ++brickCount;
		brick.update();
		
	}

}
*/



