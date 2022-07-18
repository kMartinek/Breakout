#include "vec2f.h"
#include <cmath>
#include "ball.h"
#define PI 3.14159265

vec2f::vec2f()
{
	x = 0;
	y = 0;
}

vec2f::vec2f(float i, float j) 
	:x(i), y(j)
	{}

float vec2f::angle_deg()
{
	float angle;
	if (y == 1 && x == 0) 
		return 90;
	else if (y == -1 && x == 0) 
		return 270;
	else
		angle = atan(y / x) * 180/PI;
	
	if (x > 0 && y < 0)
		angle += 360;
	else if (x < 0 && y > 0)
		angle += 180;
	else if (x < 0 && y < 0)
		angle += 180;

	return angle;
}

float vec2f::angle_rad()
{
	return atan(y / x);
}

float vec2f::getX()
{
	return x;
}

float vec2f::getY()
{
	return y;
}

void vec2f::set(float i, float j)
{
	x = i;
	y = j;
}

