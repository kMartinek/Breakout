#include <SDL.h>
#include "tinyxml2.h"
#include "level.h"
#include <iostream>
#include <algorithm>

Level::Level()
{

}

Level::Level(std::string levelFile, Graphics& graphics)
{
	brickCount = 0;

	tinyxml2::XMLDocument xmlfile;
	xmlfile.LoadFile(levelFile.c_str());

	tinyxml2::XMLElement* levelElement = xmlfile.FirstChildElement("Level");
	if (levelElement != NULL)
	{
		levelElement->QueryIntAttribute("RowCount", &rowCount);
		levelElement->QueryIntAttribute("ColumnCount", &columnCount);
		levelElement->QueryIntAttribute("RowSpacing", &rowSpacing);
		levelElement->QueryIntAttribute("ColumnSpacing", &columnSpacing);
		levelElement->QueryStringAttribute("BackgroundTexture", &backgroundTexture);
	}

	tinyxml2::XMLElement* brickTypesElement = levelElement->FirstChildElement("BrickTypes");
	if (brickTypesElement != NULL)
	{
		tinyxml2::XMLElement* brickTypeElement = brickTypesElement->FirstChildElement("BrickType");
		BrickType type;
		const char* id;
		const char* text;
		const char* hitSound;
		const char* breakSound;
		if (brickTypeElement != NULL)
		{
			while (brickTypeElement)
			{
				brickTypeElement->QueryStringAttribute("Id", &id);
				brickTypeElement->QueryStringAttribute("Texture", &text);
				brickTypeElement->QueryIntAttribute("HitPoints", &type.hitPoints);
				brickTypeElement->QueryStringAttribute("HitSound", &hitSound);
				brickTypeElement->QueryStringAttribute("BreakSound", &breakSound);
				brickTypeElement->QueryIntAttribute("BreakScore", &type.breakScore);
				
				type.id = id;
				type.texture = text;
				type.hitSound = hitSound;
				type.breakSound = breakSound;
				brickTypes[id] = type;

				brickTypeElement = brickTypeElement->NextSiblingElement("BrickType");
			}
		}

	}
	tinyxml2::XMLElement* bricksElement = brickTypesElement->NextSiblingElement("Bricks");
	if (bricksElement != NULL)
	{
		const char* clayout = bricksElement->GetText();
		layout = std::string(clayout);
		
	}
}


void Level::load(std::vector<Brick>& bricks, Graphics& graphics)
{

	float maxHeight = 50;
	float minHeight = 5;

	float brickHeight = (float)(350 - rowSpacing * (rowCount - 1)) / rowCount;
	if (brickHeight < minHeight)
	{
		std::cout << "Brick overload! Bricks are too thin! Change rowCount";
		exit;
	}
	else if (brickHeight > maxHeight)
		brickHeight = maxHeight;

	float brickWidth = (float)(800 - columnSpacing * (columnCount - 1)) / columnCount;
	float minWidth = 5;
	if (brickWidth < minWidth)
	{
		std::cout << "Brick overload! Bricks are too thin! Change columnCount";
	}

	int i, j, it = 0;



	layout.erase(std::remove_if(layout.begin(), layout.end(), std::isspace), layout.end());


	for (i = 0; i < rowCount; ++i)
	{
		for (j = 0; j < columnCount; ++j)
		{
			if (layout[it] != '_')
			{
				Brick b((int)(0 + j * (brickWidth + columnSpacing)), (int)(50 + i * (brickHeight + rowSpacing)),
					layout.substr(it,1), 100, brickTypes[layout.substr(it, 1)].hitPoints, brickTypes[layout.substr(it, 1)].texture,
					graphics, (int)brickHeight, (int)brickWidth);
				bricks.push_back(b);
				if (layout[it]!= 'I') brickCount++;
			}

			if (it + 1 < layout.size()) ++it;

		}
	}
}

void Level::draw(Graphics& graphics)
{

}