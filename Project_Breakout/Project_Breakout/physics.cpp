
#include <iostream>
#include "physics.h"
#include <cmath>
#define PI 3.14159265359

vec2f closestPoint(vec2f ball, Brick& brick)
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


vec2f closestPoint(vec2f ball, Paddle& brick)
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

float pointDistance(vec2f p1, vec2f p2)
{
	return sqrtf(powf(p1.x - p2.x, 2) + powf(p1.y - p2.y, 2));
}


//checks if there was a collision and sets the ball on the collision point
bool collisionCheckBrick(Ball& ball, Brick& brick, float& back)
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

bool collisionCheckPaddle(Ball& ball, Paddle& brick, float& back)
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



void newDirection(Ball& ball, Brick& brick)
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
			std::cout << "TOP LEFT";
			std::cout << "normal_angle: " << normal_angle << "\n";
			normal_angle += 180;
			std::cout << "normal_angle + 180" << normal_angle << "\n";
			mirror = normal_angle + 90;
			std::cout << "mirror" << mirror << "\n";
			new_angle = 2 * mirror - ball.getDirection().angle_deg() + 180;
			std::cout << "new_angle" << new_angle << "\n\n";

		}

		//bottom left corner
		else if ((clPoint.x == brick.getX()) && (clPoint.y == brick.getY() + brick.getHeight()))
		{
			std::cout << "BOTTOM LEFT";
			std::cout << "normal_angle: " << normal_angle << "\n";
			
			mirror = normal_angle + 90;
			std::cout << "mirror" << mirror << "\n";
			new_angle = 2 * mirror - ball.getDirection().angle_deg() + 180;
			std::cout << "new_angle" << new_angle << "\n\n";
		}

		//bottom right corner
		else if ((clPoint.x == brick.getX() + brick.getWidth()) && (clPoint.y == brick.getY() + brick.getHeight()))
		{
			std::cout << "BOTTOM RIGHT";
			std::cout << "normal_angle: " << normal_angle << "\n";
			normal_angle += 360;
			std::cout << "normal_angle+360: " << normal_angle << "\n";
			mirror = normal_angle + 90;
			new_angle = 2 * mirror - ball.getDirection().angle_deg() - 180;
			std::cout << "new_angle" << new_angle << "\n\n";
		}
		//upper right corner
		else
		{
			std::cout << "TOP RIGHT";
			std::cout << "normal_angle: " << normal_angle << "\n";
			normal_angle += 180;
			std::cout << "normal_angle+360: " << normal_angle << "\n";
			mirror = normal_angle + 90;
			new_angle = 2 * mirror - ball.getDirection().angle_deg() + 180;
			std::cout << "new_angle" << new_angle << "\n\n";
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
		ball.setDirection(cos(angle_rad), sin(angle_rad));
	
	}

	else if (clPoint.y == brick.getY() || clPoint.y == brick.getY() + brick.getHeight())
	{
		ball.setDirection(ball.getDirection().x, ball.getDirection().y * (-1));
		//top collision
	}

	else
	{
		//side collision
		ball.setDirection(ball.getDirection().x * (-1), ball.getDirection().y);
	}


}


bool collisionCheckFloor(Ball& ball)
{
	if (ball.getPosition().y + ball.getDirection().y >= 600)
		return true;
	else
		return false;
}



bool collisionCheckWall(Ball& ball)
{
	bool collision = false;
	if (ball.getPosition().x <= 0)
	{
		ball.setDirection(ball.getDirection().x * (-1), ball.getDirection().y);
		ball.setPosition(0, ball.getPosition().y);
		collision = true;
	}
	else if (ball.getPosition().x  >= 800 - 2*ball.getRadius())
	{
		ball.setDirection(ball.getDirection().x * (-1), ball.getDirection().y);
		ball.setPosition(800 - 2*ball.getRadius(), ball.getPosition().y);
		collision = true;
	
	}
	

	if (ball.getPosition().y  <= 0)
	{
		ball.setDirection(ball.getDirection().x, ball.getDirection().y * (-1));
		ball.setPosition(ball.getPosition().x, 0);
		collision = true;
	}
	
	return collision;

}



void newDirectionPaddle(Ball& ball, Paddle& paddle)
{
	vec2f clPoint = closestPoint(ball.getCenter(), paddle);

	if (clPoint.y == paddle.getY())
	{
		float ratioHit = 1 - (clPoint.x - paddle.getX()) / paddle.getWidth();
		float angle_deg = 30 + ratioHit * 120;

		float angle_rad = angle_deg * (PI / 180);

		ball.setDirection(cos(angle_rad), -sin(angle_rad));
		paddle.lastFrameCollisionL = false;
		paddle.lastFrameCollisionR = false;
	}
	

	else if (clPoint.x == paddle.getX())
	{
		if (!paddle.CollisionL())
		{
			ball.setDirection(ball.getDirection().x * (-1), ball.getDirection().y);
			paddle.lastFrameCollisionL = true;
			paddle.lastFrameCollisionR = false;
		}
		else
		{
			ball.setPosition(paddle.getX(), ball.getPosition().y);
			paddle.lastFrameCollisionL = true;
			paddle.lastFrameCollisionR = false;
		}
	}
	else
	{
		if(!paddle.CollisionR())
		{
			ball.setDirection(ball.getDirection().x * (-1), ball.getDirection().y);
			paddle.lastFrameCollisionL = false;
			paddle.lastFrameCollisionR = true;
		}
		else
		{
			ball.setPosition(paddle.getX()+paddle.getWidth(), ball.getPosition().y);
			paddle.lastFrameCollisionL = false;
			paddle.lastFrameCollisionR = true;
		}
	}
}





