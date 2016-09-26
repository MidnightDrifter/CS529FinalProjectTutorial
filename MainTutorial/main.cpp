//#include <glew.h>
#include <SDL.h>
#include <glew.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "Sprite.h"
#pragma comment (lib, "glew32.lib")
# define GL3_PROTOTYPES 1
const int SCREEN_HEIGHT = 800;
const int SCREEN_WIDTH = 1200;
const int OPEN_GL_MAJOR_VERSION = 3; //OpenGL version 3.x
const int OPEN_GL_MINOR_VERSION = 2;  // OpenGL version x.2
const int USE_DOUBLE_BUFFER = 1;  //1 = use double buffering
//Woo
int test;

SDL_Window* window;
SDL_Surface* surface;
SDL_GLContext context;
//See :  lazyfoo.net for SDL2 stuff, learnopengl.com for OpenGL stuff, headerphile.com/sdl/ for combining the two

//Actually just go with headerphile, combining stuff is just baaaaaad

bool Init()
{
	// Initialize SDL's Video subsystem
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "Failed to init SDL\n";
		return false;
	}

	// Create our window centered at 512x512 resolution
window = SDL_CreateWindow("Test Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);

	// Check that everything worked out okay
	if (!window)
	{
		std::cout << "Unable to create window\n";
		//CheckSDLError(__LINE__);
		return false;
	}

	// Create our opengl context and attach it to our window
	context = SDL_GL_CreateContext(window);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, OPEN_GL_MAJOR_VERSION);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, OPEN_GL_MINOR_VERSION);  //OpenGL ver 3.2

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, USE_DOUBLE_BUFFER);  //Self-explanatory


	// This makes our buffer swap syncronized with the monitor's vertical refresh
	SDL_GL_SetSwapInterval(1);

	// Init GLEW
	// Apparently, this is needed for Apple. Thanks to Ross Vander for letting me know
#ifndef __APPLE__
	glewExperimental = GL_TRUE;
	glewInit();
#endif

	return true;
}




class Shader
{
public:
	std::string ReadFile(const char* file)
	{
		// Open file
		std::ifstream t(file);

		// Read file into buffer
		std::stringstream buffer;
		buffer << t.rdbuf();

		// Make a std::string and fill it with the contents of buffer
		std::string fileContent = buffer.str();

		return fileContent;
	}

	void BindAttributeLocation(int index, const std::string &attribute)
	{
		// Bind attribute index 0 (coordinates) to in_Position and attribute index 1 (color) to in_Color
		// Attribute locations must be setup before calling glLinkProgram
		glBindAttribLocation(shaderProgram, index, attribute.c_str());
		//Or, alternatively, I can use this myself to name my own attributes and locations--currently it refers to locations in the VAO
	}

	void UseProgram()
	{
		// Load the shader into the rendering pipeline
		glUseProgram(shaderProgram);
	}

	bool Init()
	{
		// Generate our shader. This is similar to glGenBuffers() and glGenVertexArray(), except that this returns the ID
		shaderProgram = glCreateProgram();

		// Bind the location of our attributes
		BindAttributeLocation(0, "in_Position");
	//	BindAttributeLocation(1, "in_Color");

		if (!LoadVertexShader("tutorialVertexShader.vert"))
			return false;

		if (!LoadFragmentShader("tutorialFragmentShader.frag"))
			return false;

		// All shaders has been create, now we must put them together into one large object
		return LinkShaders();
	}


	bool LoadVertexShader(const std::string &filename)
	{
		std::cout << "Linking Vertex shader" << std::endl;

		// Read file as std::string 
		std::string str = ReadFile(filename.c_str());

		// c_str() gives us a const char*, but we need a non-const one
		char* src = const_cast<char*>(str.c_str());
		int32_t size = str.length();

		// Create an empty vertex shader handle
		vertexshader = glCreateShader(GL_VERTEX_SHADER);

		// Send the vertex shader source code to OpenGL
		glShaderSource(vertexshader, 1, &src, &size);

		// Compile the vertex shader
		glCompileShader(vertexshader);

		int wasCompiled = 0;
		glGetShaderiv(vertexshader, GL_COMPILE_STATUS, &wasCompiled);

		if (wasCompiled == 0)
		{
			PrintShaderCompilationErrorInfo(vertexshader);
			return false;
		}

		glAttachShader(shaderProgram, vertexshader);
		return true;
	}

	bool LoadFragmentShader(const std::string &filename)
	{
		std::cout << "Loading Fragment Shader" << std::endl;

		// Read file as std::string 
		std::string str = ReadFile(filename.c_str());

		// c_str() gives us a const char*, but we need a non-const one
		char* src = const_cast<char*>(str.c_str());
		int32_t size = str.length();

		// Create an empty vertex shader handle
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Send the vertex shader source code to OpenGL
		glShaderSource(fragmentShader, 1, &src, &size);

		// Compile the vertex shader
		glCompileShader(fragmentShader);

		int wasCompiled = 0;
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &wasCompiled);

		if (wasCompiled == false)
		{
			PrintShaderCompilationErrorInfo(fragmentShader);
			return false;
		}

		glAttachShader(shaderProgram, fragmentShader);
		return true;
	}

	bool LinkShaders()
	{
		// Link. At this point, our shaders will be inspected/optized and the binary code generated
		// The binary code will then be uploaded to the GPU
		glLinkProgram(shaderProgram);

		// Verify that the linking succeeded
		int isLinked;
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, (int *)&isLinked);

		if (isLinked == false)
			PrintShaderLinkingError(shaderProgram);

		return isLinked != 0;
	}

	void PrintShaderLinkingError(int32_t shaderId)
	{
		std::cout << "=======================================\n";
		std::cout << "Shader linking failed : " << std::endl;

		// Find length of shader info log
		int maxLength;
		glGetProgramiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);

		std::cout << "Info Length : " << maxLength << std::endl;

		// Get shader info log
		char* shaderProgramInfoLog = new char[maxLength];
		glGetProgramInfoLog(shaderProgram, maxLength, &maxLength, shaderProgramInfoLog);

		std::cout << "Linker error message : " << shaderProgramInfoLog << std::endl;

		/* Handle the error in an appropriate way such as displaying a message or writing to a log file. */
		/* In this simple program, we'll just leave */
		delete shaderProgramInfoLog;
		return;
	}

	// If something went wrong whil compiling the shaders, we'll use this function to find the error
	void PrintShaderCompilationErrorInfo(int32_t shaderId)
	{
		std::cout << "=======================================\n";
		std::cout << "Shader compilation failed : " << std::endl;

		// Find length of shader info log
		int maxLength;
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);

		// Get shader info log
		char* shaderInfoLog = new char[maxLength];
		glGetShaderInfoLog(shaderId, maxLength, &maxLength, shaderInfoLog);

		// Print shader info log
		std::cout << "\tError info : " << shaderInfoLog << std::endl;

		std::cout << "=======================================\n\n";
		delete shaderInfoLog;
	}

	void CleanUp()
	{
		/* Cleanup all the things we bound and allocated */
		glUseProgram(0);
		glDetachShader(shaderProgram, vertexshader);
		glDetachShader(shaderProgram, fragmentShader);

		glDeleteProgram(shaderProgram);


		glDeleteShader(vertexshader);
		glDeleteShader(fragmentShader);
	}

	// The handle to our shader program
	GLuint shaderProgram;

	// The handles to the induvidual shader
	GLuint vertexshader, fragmentShader;

};




int main(int argc, char* argv[])
{
	//return 0;



	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return -1;
	}

	else
	{
		

		//Create window
		//window = SDL_CreateWindow("Test Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
		if (!Init())
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			return -1;
		}

		else
		{
			/*
			int SDL_GL_SetAttribute
			(
				SDL_GLattr attr,
				int value
			)
			*/
	
			//context= SDL_GL_CreateContext(window);
			//glewExperimental = true;
			//if (!glewInit())
			//{
			//	exit(-1);
			//}
		//	glewInit();
			//Experimental and glewInit come AFTER the context is made
			//glewExperimental = true;   //Uncomment to use later OpenGL stuff

			glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			SDL_GL_SwapWindow(window);

			Sprite s;
			s.genTriangleSprite();
			s.draw(window);

			//Fill window with color--in this case, black
			int i = 0;




			//GAME LOOP HERE

			//Destroy context and window

			
			SDL_GL_DeleteContext(context);

			// Destroy our window
			SDL_DestroyWindow(window);

			// Shutdown SDL 2
			SDL_Quit();
		}
	}
}