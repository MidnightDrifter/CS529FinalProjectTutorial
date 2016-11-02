#include "SpriteBasic.h"
extern ResourceManager ResourceMgr;


SpriteBasic::SpriteBasic(): Component(COMPONENT_TYPE::SPRITE), spriteName("")
{

}


SpriteBasic::~SpriteBasic()
{
}

void SpriteBasic::Update()
{

}

void SpriteBasic::Serialize(FILE** fpp)
{
	std::string name("Resources\\");
	std::string file;
	fscanf_s(*fpp, "%s\n",&file);
	name += file;
	spriteName = name;
	ResourceMgr.loadSurface(name.c_str());

}