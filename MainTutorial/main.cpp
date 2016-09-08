//#include <glew.h>
#include <SDL.h>
#include <glew.h>
#include <stdio.h>

const int SCREEN_HEIGHT = 800;
const int SCREEN_WIDTH = 1200;


int main(int argc, char* argv[])
{
	return 0;

	SDL_Window* window;
	SDL_Surface* surface;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}

	else
	{
		//Create window
		window = SDL_CreateWindow("Test Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
	}
}