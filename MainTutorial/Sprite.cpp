#include "Sprite.h"


Sprite::Sprite() : Component(COMPONENT_TYPE::SPRITE)
{
	
		for (int i = 0; i < 12; i++)
		{
			vertices[i] = 0;
		}

		for (int i = 0; i < 4; i++)
		{
			colorHolder[i] = 0;
		}

		for (int i = 0; i < 16; i++)
		{
			colors[i] = 0;
		}



}

Sprite::~Sprite()
{
	delete[] vertices;
	delete[] colors;
	delete[] colorHolder;
}

/*
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
*/

void Sprite::Serialize(FILE** fpp)
{
	fscanf(*fpp, "%f %f %f %f\n", &colorHolder[0], &colorHolder[1], &colorHolder[2], &colorHolder[3]);
	fscanf(*fpp, "%i\n", &numVertices);

	//vertices = new GLfloat(3 * numVertices);

		fscanf(*fpp, "%f %f %f %f %f %f %f %f %f %f %f %f\n", &vertices[0], &vertices[1], &vertices[2], &vertices[3], &vertices[4], &vertices[5], &vertices[6], &vertices[7], &vertices[8], &vertices[9],&vertices[10],&vertices[11]);
	
}


void Sprite::GenerateBuffers()
{
	//colors[0] = colors[3] = colors[6] = colorHolder[0];
	colors[0] = colors[4] = colors[8] = colors[12]=colorHolder[0];
	colors[1] = colors[5] = colors[9] = colors[13] = colorHolder[1];
	colors[2] = colors[6] = colors[10] = colors[14] = colorHolder[2];
		colors[3] = colors[7] = colors[11] = colors[15] = colorHolder[3];
	glGenBuffers(1, &posBuffID);  //Position buffer
	glGenBuffers(1, &colorBuffID);  //Color buffer

	int vertexNum = 3;   //Number of vertices
	int coordsPerPosition = 3;    // (x,y,z)
	int colorsPerPosition = 4;   //4 vals per color, RGBA

	int posBufferSize = vertexNum * coordsPerPosition * sizeof(GLfloat);
	int colorBufferSize = vertexNum * colorsPerPosition * sizeof(GLfloat);


	//Pass position buffer to OpenGL, graphics card
	glBindBuffer(GL_ARRAY_BUFFER, posBuffID);   //Specify buffer
	glBufferData(GL_ARRAY_BUFFER, posBufferSize, vertices, GL_STATIC_DRAW);  //Specify data inside buffer--what kind of format, size of buffer, pointer to data, what to do with the data
	glBindBuffer(GL_ARRAY_BUFFER, 0);  //Clear what buffer you're bound to

	glBindBuffer(GL_ARRAY_BUFFER, colorBuffID);  //Pass color buffer to OpenGl, graphics card
	glBufferData(GL_ARRAY_BUFFER, colorBufferSize, colors, GL_STATIC_DRAW);  //Specify data inside buffer--what kind of format, size of buffer, pointer to data, what to do with the data
	glBindBuffer(GL_ARRAY_BUFFER, 0);   //Clear what buffer you're bound to

}