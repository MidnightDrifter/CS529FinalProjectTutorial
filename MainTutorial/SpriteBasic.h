#pragma once

#include "Component.h"
#include "ResourceManager.h"
#include <SDL.h>
#include <string>
class SpriteBasic :
	public Component
{
public:
	SpriteBasic();
	virtual ~SpriteBasic();
	void Serialize(FILE** fpp);
	void Update();
	SDL_Surface getSprite();

private:

	std::string spriteName;

};

