#include "GraphicsManager.h"


/*
GraphicsManager::GraphicsManager()
{

	//Step 1 - make program
	globalShaderIDs[(int)(SHADER_TYPE::COLOR)] = glCreateProgram();

	//Step 2 - make vertex & pixel shaders, create + compile

	//Vertetx shader

	const char * vertexShaderCode =  "uniform mat4 transform;\
									  attribute vec4 aPosition;\
									  attribute vec4 aColor;\
									  attribute vec2 aTextureCoordinates;\
									  varying vec2 vTextureCoordinates;\
									  varying vec4 vColor;\
									  void main() \
									{\
									vec4 worldPos = transform * aPosition;\
									vColor = aColor;  gl_Position = worldPos;\
									}", ;




	const char* fragmentShaderCode[2] = { "varying vec4 vColor;									\
										varying vec2 vTextureCoordinates;						\
										uniform sampler2D testTexture;							\
									  void main()												\
									 {															\
									gl_FragColor = vColor;									\
									//glFragColor = texture2D(testTexture,vTextureCoordinates;)\
									} ",
										"varying vec4 vColor;									\
										varying vec2 vTextureCoordinates;						\
										uniform sampler2D testTexture;							\
									  void main()												\
									 {															\
									//gl_FragColor = vColor;									\
									glFragColor = texture2D(testTexture,vTextureCoordinates;)\
									} "

	};

	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderID, 1, &vertexShaderCode, NULL);
	glCompileShader(vertexShaderID);

	GLint status;
	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &status);
	if (status == GL_TRUE)
	{
		glAttachShader(globalShaderIDs[(int)(SHADER_TYPE::COLOR)], vertexShaderID);
	}

	GLuint fragShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShaderID, 1, &fragmentShaderCode, NULL);
	glCompileShader(fragShaderID);

	glGetShaderiv(fragShaderID, GL_COMPILE_STATUS, &status);
	if (status == GL_TRUE)
	{
		glAttachShader(globalShaderIDs[(int)(SHADER_TYPE::COLOR)], fragShaderID);
	}

	//3)  Link program
	glLinkProgram(globalShaderIDs[(int)(SHADER_TYPE::COLOR)]);
	//4)  Use program
	glUseProgram(globalShaderID);



}


GraphicsManager::~GraphicsManager()
{
}
*/