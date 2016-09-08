//#include <glew.h>
#include <SDL.h>
#include <glew.h>
#include <stdio.h>

const int SCREEN_HEIGHT = 800;
const int SCREEN_WIDTH = 1200;
const int OPEN_GL_VERSION = 2;  // OpenGL version 3.x
const int USE_DOUBLE_BUFFER = 1;  //1 = use double buffering


//See :  lazyfoo.net for SDL2 stuff, learnopengl.com for OpenGL stuff, headerphile.com/sdl/ for combining the two

int main(int argc, char* argv[])
{
	//return 0;

	SDL_Window* window;
	SDL_Surface* surface;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return -1;
	}

	else
	{
		//Create window
		window = SDL_CreateWindow("Test Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
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

			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, OPEN_GL_VERSION);  //OpenGL ver 3.2

			SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, USE_DOUBLE_BUFFER);  //Self-explanatory

			SDL_GLContext SDL_GL_CreateContext(window);
			//glewExperimental = true;   //Uncomment to use later OpenGL stuff
		}
	}
}