#pragma once

#include "Component.h"
#include "ResourceManager.h"
#include <string>
class SpriteBasic :
	public Component
{
public:
	SpriteBasic();
	virtual ~SpriteBasic();
	void Serialize(FILE** fpp);
	void Update();


private:

	std::string spriteName;

};

