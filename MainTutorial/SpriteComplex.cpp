#include "SpriteComplex.h"



SpriteComplex::SpriteComplex() : isSquare(false), Component(COMPONENT_TYPE::SPRITE)
{
}

SpriteComplex::SpriteComplex(bool b) : isSquare(b), Component(COMPONENT_TYPE::SPRITE) {}

SpriteComplex::~SpriteComplex()
{
}

void SpriteComplex::Serialize(FILE** fpp)
{

}

void SpriteComplex::Update()
{

}