#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <map>
#include <vector>
#include "graphics.h"
#include <map>
#include "brick_type.h"
#include "brick.h"

class Level
{
/*private:
	int rowCount;
	int columnCount;
	int rowSpacing;
	int columnSpacing;
	const char* backgroundTexture;
	const char* layout;
	std::map<std::string, BrickType> brickTypes;
	*/
	//SDL_Texture* texture;


public:
	Level();
	Level(std::string level, Graphics& graphics);

	int rowCount;
	int columnCount;
	int rowSpacing;
	int columnSpacing;
	const char* backgroundTexture;
	std::string layout;
	std::map<std::string, BrickType> brickTypes;

	int brickCount;


	void draw(Graphics& graphics);
	void load(std::vector<Brick>& bricks, Graphics& graphics);
};