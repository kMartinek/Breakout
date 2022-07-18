#include "brick_type.h"

BrickType::BrickType()
{
	id = "";
	texture = "";
	hitPoints = 0;
	breakScore = 0;
	breakSound = "";
	hitSound = "";
}

BrickType::BrickType(const BrickType& type)
{
	id = type.id;
	texture = type.texture;
	hitPoints = type.hitPoints;
	breakSound = type.breakSound;
	hitSound = type.hitSound;

}