#pragma once


struct vec2f
{
	float x, y;
	
	vec2f();
	vec2f(float i, float j);
	
	float angle_rad();
	float angle_deg();

	float getX();
	float getY();

	void set(float new_x, float new_y);

};