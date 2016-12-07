#include "SpriteBasic.h"
extern ResourceManager& ResourceMgr;



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
	float i, j;
	fscanf(*fpp, "%s %i %i\n", &file, &width, &height);//&i, &j);
	name += file;
	spriteName = name;
	//width = ResourceMgr.loadSurface(name)->w;
	//height = ResourceMgr.loadSurface(name)->h;
	
}