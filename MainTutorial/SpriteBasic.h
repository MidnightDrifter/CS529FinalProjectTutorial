#pragma once

#include "Component.h"
#include "ResourceManager.h"
#include <SDL.h>
#include <string>
class SpriteBasic :
	public Component
{
public:
	SpriteBasic() : Component(COMPONENT_TYPE::SPRITE), width(0), height(0) {}
	SpriteBasic(const char* c) : spriteName(c), width(0), height(0), Component(COMPONENT_TYPE::SPRITE) {}
	SpriteBasic(std::string s) : spriteName(s), width(0), height(0), Component(COMPONENT_TYPE::SPRITE) {}
	SpriteBasic(std::string s, int w, int h) : spriteName(s), width(w), height(h), Component(COMPONENT_TYPE::SPRITE){}
	SpriteBasic(const char* c, int w, int h) : spriteName(c), width(w), height(h), Component(COMPONENT_TYPE::SPRITE){}
	virtual ~SpriteBasic();
	void Serialize(FILE** fpp);
	void Update();
	SDL_Surface* getSprite();

	int width, height;

private:

	std::string spriteName;
	
};

