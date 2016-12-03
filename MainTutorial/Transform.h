#pragma once
#include "Component.h"
#include "transformMAT4.h"
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

	void setX(float f) { xPos = f; }
	void setY(float f) { yPos = f; }

	float getX() { return xPos; }
	float getY() { return yPos; }

	void setXScale(float f) { xScale = f; }
	void setYScale(float f) { yScale = f; }
	void setRotation(float f) { rotation = f; }


	float getXScale() const { return xScale; }
	float getYScale() const { return yScale; }
	float getRotation() const { return rotation; }  //check degree vs. rad ???

	float rotation;

	MAT4 transformMatrix;

private:
	float xPos;
	float yPos;
	float xScale;
	float yScale;

	


};

