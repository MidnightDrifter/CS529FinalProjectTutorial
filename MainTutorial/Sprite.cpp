#include "Sprite.h"


GLuint Sprite::getArrayBufferID() const
{
	return arrayBufferID;
}

bool Sprite::getIsSquare() const
{
	return isSquare;
}

void Sprite::genSquareSprite()
{
	isSquare = true;
	GLuint bufferID;
	glGenBuffers(1, &bufferID);
	//glBindBuffer(GL_ARRAY_BUFFER, arrayBufferID);
	glGenVertexArrays(1, &arrayBufferID);
	glBufferData(GL_ARRAY_BUFFER, (sizeof(GLfloat) * 12), Sprite::square, GL_STATIC_DRAW);
	//Square so 4 points & 3 vertices per point--12 floats total

	glBindVertexArray(arrayBufferID);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//array index, number of points in our float arrays (3 for x,y,z), data stored inside array,
	//whether data should be normalized, interval between vertex attributes (unused), starting point of data to use (unused)
	glEnableVertexAttribArray(arrayBufferID);
}

void Sprite::genTriangleSprite()
{
	isSquare = false;
	GLuint bufferID;
	glGenBuffers(1, &bufferID);
	//glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	glGenVertexArrays(1, &arrayBufferID);
	glBufferData(GL_ARRAY_BUFFER, (sizeof(GLfloat) * 9), Sprite::triangle, GL_STATIC_DRAW);
	//Triangle so 3 points & 3 vertices per point -- 9 floats total

	glBindVertexArray(arrayBufferID);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);  
	//array index, number of points in our float arrays (3 for x,y,z), data stored inside array,
	//whether data should be normalized, interval between vertex attributes (unused), starting point of data to use (unused)
	glEnableVertexAttribArray(arrayBufferID);
}

void Sprite::draw(SDL_Window* win)
{
	int q=3;
	if(isSquare)
	{
		q++;
	}

	glDrawArrays(GL_TRIANGLE_FAN, 0, q);
	SDL_GL_SwapWindow(win);
}

Sprite::Sprite()
{
}


Sprite::~Sprite()
{
}

