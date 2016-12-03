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
{/*
	xPos = xPos;
	yPos = yPos;
	xScale = xScale;
	yScale = yScale;
	rotation = rotation;
	//Check degree vs. rotation for Rotate???
	transformMatrix = Translate(xPos, yPos, 0) * Scale(xScale, yScale, 1) * Rotate(2, rotation);

	*/
	}


void Transform::Serialize(FILE** fpp)
{
	fscanf(*fpp, "%f %f %f %f %f\n", &xPos, &yPos, &xScale, &yScale, &rotation);
}