#pragma once
#include "Component.h"
class Transform :
	public Component
{
public:
	Transform();
	Transform(float x, float y);
	virtual ~Transform();
	void Update();
	void Serialize(FILE** fpp);
	void plusEqualX(float f) {xPos += f; }
	void plusEqualY(float f) { yPos += f; }
	void minusEqualX(float f) { xPos -= f; }
	void minusEqualY(float f) { yPos -= f; }

	float getX() { return xPos; }
	float getY() { return yPos; }

private:
	float xPos;
	float yPos;

};

