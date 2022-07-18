#pragma once
#include <string>

class BrickType
{
protected:
	BrickType(const BrickType& type);
public:
	std::string id;
	std::string texture;
	int hitPoints;
	int breakScore;
	std::string breakSound;
	std::string hitSound;

	//poku�aji sa const charom umjesto stringa
	BrickType();
	
};