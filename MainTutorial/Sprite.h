#pragma once
#include <glew.h>
#include <SDL.h>
#include <stdio.h>
#include "Component.h"

//#include "shader.h"
#pragma comment (lib, "glew32.lib")
class Sprite : public Component
{
public:
	Sprite();// : Component(COMPONENT_TYPE::SPRITE) {  }
	~Sprite(); // { delete[] vertices;  delete[] colors;  delete[] colorHolder; }
	void Update() {}
	void Serialize(FILE** fpp);
	void GenerateBuffers();
	/*
	const GLfloat square[4][3]
	{

			{ -0.5f,  0.5f,  0.5 }, // Top left
			{ 0.5,  0.5,  0.5 }, // Top right
			{ 0.5, -0.5,  0.5 }, // Bottom right 
			{ -0.5, -0.5,  0.5 }, // Bottom left

	};

	const GLfloat triangle[3][3]
	{
		{-0.5f, -0.5f, 0.5f},  //Bottom left
		{0.5f, -0.5f, 0.5f },  //Bottom right
		{0.0f, 0.5f, 0.5f}  //Top middle
	};
	*/
	float colorHolder[4];
	GLfloat colors[16];
	GLfloat vertices[12];
	int numVertices;
	GLuint colorBuffID, posBuffID;

//	GLuint getArrayBufferID() const;
//	bool getIsSquare() const; 
	//void genSquareSprite(Shader s);  //Add in filename / filepath thing?
	//void genTriangleSprite(Shader s);
//	void draw(SDL_Window* win);





	//bool isSquare;
	//int numRows;  //Num rows = number of points in sprite
	//int numCols;  //Num cols = number of floats per point (2D vs 3D)


};

