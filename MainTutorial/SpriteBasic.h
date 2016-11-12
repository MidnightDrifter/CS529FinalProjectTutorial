#pragma once

#include "Component.h"
#include "ResourceManager.h"
#include <SDL.h>
#include <string>
class SpriteBasic :
	public Component
{
public:
	SpriteBasic() : Component(COMPONENT_TYPE::SPRITE) {}
	SpriteBasic(const char* c) : spriteName(c), Component(COMPONENT_TYPE::SPRITE) {}
	SpriteBasic(std::string s) : spriteName(s), Component(COMPONENT_TYPE::SPRITE) {}
	virtual ~SpriteBasic();
	void Serialize(FILE** fpp);
	void Update();
	SDL_Surface* getSprite();

private:

	std::string spriteName;

};

