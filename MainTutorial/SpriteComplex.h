#pragma once
#include <glfw3.h>
#include "Component.h"
class SpriteComplex :
	public Component
{
	//Only gonna have squares and triangles--here are the mesh vertices
	const GLfloat square[4][3]
	{

		{ -0.5f,  0.5f,  0.5 }, // Top left
		{ 0.5,  0.5,  0.5 }, // Top right
		{ 0.5, -0.5,  0.5 }, // Bottom right 
		{ -0.5, -0.5,  0.5 }, // Bottom left

	};

	const GLfloat triangle[3][3]
	{
		{ -0.5f, -0.5f, 0.5f },  //Bottom left
		{ 0.5f, -0.5f, 0.5f },  //Bottom right
		{ 0.0f, 0.5f, 0.5f }  //Top middle
	};



public:
	SpriteComplex();
	SpriteComplex(bool t);
	~SpriteComplex();
	void Serialize(FILE** fpp);
	void Update();

private:
	bool isSquare;



};

