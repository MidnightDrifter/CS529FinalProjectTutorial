#include "SpriteBasic.h"
extern ResourceManager ResourceMgr;



SpriteBasic::~SpriteBasic()
{
}

void SpriteBasic::Update()
{

}

SDL_Surface* SpriteBasic::getSprite()
{
	return (ResourceMgr.loadSurface(spriteName));
}

void SpriteBasic::Serialize(FILE** fpp)
{
	std::string name("Resources\\");
	char file[100];
	fscanf(*fpp, "%s\n",&file);
	name += file;
	spriteName = name;
	ResourceMgr.loadSurface(name);

}