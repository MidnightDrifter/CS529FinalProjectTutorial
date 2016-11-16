#include "Transform.h"

//extern InputManager InputMgr;


Transform::Transform() : Component(COMPONENT_TYPE::TRANSFORM)
{
}

Transform::Transform(float x, float y) : Component(COMPONENT_TYPE::TRANSFORM), xPos(x), yPos(y) {}

Transform::~Transform()
{
}


void Transform::Update()
{

}


void Transform::Serialize(FILE** fpp)
{
	fscanf(*fpp, "%f %f\n", &xPos, &yPos);
}