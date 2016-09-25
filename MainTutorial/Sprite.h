#pragma once
#include <glew.h>
#include <SDL.h>
#pragma comment (lib, "glew32.lib")
class Sprite
{
public:
	Sprite();
	~Sprite();

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

	GLuint getArrayBufferID() const;
	bool getIsSquare() const; 
	void genSquareSprite();  //Add in filename / filepath thing?
	void genTriangleSprite();
	void draw(SDL_Window* win);


private:
	GLuint arrayBufferID;
	bool isSquare;
	//int numRows;  //Num rows = number of points in sprite
	//int numCols;  //Num cols = number of floats per point (2D vs 3D)


};

