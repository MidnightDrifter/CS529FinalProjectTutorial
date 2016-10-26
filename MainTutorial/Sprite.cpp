#include "Sprite.h"


GLuint Sprite::getArrayBufferID() const
{
	return arrayBufferID;
}

bool Sprite::getIsSquare() const
{
	return isSquare;
}

void Sprite::genSquareSprite(Shader s)
{
	isSquare = true;
	GLuint bufferID;
	glGenBuffers(1, &bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, arrayBufferID);
	glGenVertexArrays(1, &arrayBufferID);
	
	glBufferData(GL_ARRAY_BUFFER, (sizeof(GLfloat) * 12), Sprite::square, GL_STATIC_DRAW);
	//Square so 4 points & 3 vertices per point--12 floats total

	glBindVertexArray(arrayBufferID);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//array index, number of points in our float arrays (3 for x,y,z), data stored inside array,
	//whether data should be normalized, interval between vertex attributes (unused), starting point of data to use (unused)
	glEnableVertexAttribArray(arrayBufferID);

	if (!s.Init())
		exit(-1);

	s.UseProgram();

	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void Sprite::genTriangleSprite(Shader s)
{
	isSquare = false;
	GLuint bufferID[1];
	glGenBuffers(1, bufferID);
	glGenVertexArrays(1, &arrayBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, bufferID[0]);
	
	glBufferData(GL_ARRAY_BUFFER, (sizeof(GLfloat) * 9), Sprite::triangle, GL_STATIC_DRAW);
	//Triangle so 3 points & 3 vertices per point -- 9 floats total

	glBindVertexArray(arrayBufferID);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);  
	//array index, number of points in our float arrays (3 for x,y,z), data stored inside array,
	//whether data should be normalized, interval between vertex attributes (unused), starting point of data to use (unused)
	glEnableVertexAttribArray(arrayBufferID);


	//SHADER STUFF & CALL GOES HERE

	if (!s.Init())
		exit(-1);

	s.UseProgram();

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::draw(SDL_Window* win)
{
	int q=3;
	if(isSquare)
	{
		q++;
	}
	//glDrawArrays didn't work, trying glDrawArraysEXT
	glDrawArrays(GL_TRIANGLE_FAN, 0, q);
	SDL_GL_SwapWindow(win);
}

Sprite::Sprite()
{
}


Sprite::~Sprite()
{
	arrayBufferID = -1;
	isSquare = false;
}

