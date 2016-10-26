//#include <glew.h>
#include <SDL.h>
#include <SDL_image.h>
#include "InputManager.h"
#include <glew.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "FramerateController.h"
#include "Sprite.h"
#include "shader.h"
#include <Windows.h>
#include "ResourceManager.h"
#pragma comment (lib, "glew32.lib")
# define GL3_PROTOTYPES 1
const int SCREEN_HEIGHT = 800;
const int SCREEN_WIDTH = 1200;
const int OPEN_GL_MAJOR_VERSION = 3; //OpenGL version 3.x
const int OPEN_GL_MINOR_VERSION = 2;  // OpenGL version x.2
const int USE_DOUBLE_BUFFER = 1;  //1 = use double buffering
//Woo
int test;
//Shader shader;
SDL_Window* window;
SDL_Surface* surface;
SDL_Surface* winSurface;
SDL_GLContext context;
InputManager InputMgr = InputManager();
FramerateController framerateController = FramerateController(5);
ResourceManager resourceMgr = ResourceManager();
//See :  lazyfoo.net for SDL2 stuff, learnopengl.com for OpenGL stuff, headerphile.com/sdl/ for combining the two

//Actually just go with headerphile, combining stuff is just baaaaaad
/*
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
	/*
	// Create our Opengl context and attach it to our window
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
*/






int main(int argc, char* argv[])
{
	if (AllocConsole())
	{
		FILE* file;
		freopen_s(&file, "CONOUT$", "wt", stdout);
		freopen_s(&file, "CONOUT$", "wt", stderr);
		freopen_s(&file, "CONOUT$", "wt", stdin);

		SetConsoleTitle("SDL 2.0 Testing Stuff");
	}


	resourceMgr.loadSurface("Resources\\darkpursuit.bmp");
	resourceMgr.loadSurface("Resources\\dark_pursuit_small_down.bmp");
	resourceMgr.loadSurface("Resources\\dark_pursuit_small_left.bmp");
	resourceMgr.loadSurface("Resources\\dark_pursuit_small_right.bmp");

	//SDL_Surface* ppImage[4] = { NULL, NULL, NULL, NULL };

	//ppImage[0] = SDL_LoadBMP("..\\Resources\\darkpursuit.bmp");
	//ppImage[0] = SDL_LoadBMP("Resources\\darkpursuit.bmp");
	//ppImage[1] = SDL_LoadBMP("Resources\\dark_pursuit_small_down.bmp");
	//ppImage[2] = SDL_LoadBMP("Resources\\dark_pursuit_small_left.bmp");
	//ppImage[3] = SDL_LoadBMP("Resources\\dark_pursuit_small_right.bmp");

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return -1;
	}

	else
	{
		//return 0;
		//printf
		window = SDL_CreateWindow("Test Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		// Check that everything worked out okay
		if (!window)
		{
			std::cout << "Unable to create window\n";
			//CheckSDLError(__LINE__);
			return false;
		}
		winSurface = SDL_GetWindowSurface(window);
		SDL_Surface * currentSurface = resourceMgr.loadSurface("Resources\\darkpursuit.bmp");
		SDL_BlitSurface(currentSurface, NULL, winSurface, NULL);
		SDL_UpdateWindowSurface(window);
		//Create window
		//window = SDL_CreateWindow("Test Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);

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




		//	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		//	glClear(GL_COLOR_BUFFER_BIT);
		//	SDL_GL_SwapWindow(window);

		//	Sprite s;
			//			s.genTriangleSprite(shader);
						//s.draw(window);

						//Fill window with color--in this case, black
		//	int i = 0;
			bool isRunning = true;
			int testing = 0;
			while (isRunning)
			{
				framerateController.FrameStart();
				
				
				SDL_Event e;
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
						isRunning = false;
					}
				}
				
				



				
				

				if (InputMgr.isKeyPressed(SDL_SCANCODE_UP))
				{
					currentSurface = resourceMgr.loadSurface("Resources\\darkpursuit.bmp");
					//SDL_BlitSurface(ppImage[0], NULL, winSurface, NULL);
					//SDL_UpdateWindowSurface(window);
				}

				else if (InputMgr.isKeyPressed(SDL_SCANCODE_DOWN))
				{

					currentSurface = resourceMgr.loadSurface("Resources\\dark_pursuit_small_down.bmp");
					//SDL_BlitSurface(ppImage[1], NULL, winSurface, NULL);
					//SDL_UpdateWindowSurface(window);
				}

				else if (InputMgr.isKeyPressed(SDL_SCANCODE_LEFT))
				{
					currentSurface = resourceMgr.loadSurface("Resources\\dark_pursuit_small_left.bmp");
					//SDL_BlitSurface(ppImage[2], NULL, winSurface, NULL);
					//SDL_UpdateWindowSurface(window);
				}

				else if (InputMgr.isKeyPressed(SDL_SCANCODE_RIGHT))
				{
					currentSurface = resourceMgr.loadSurface("Resources\\dark_pursuit_small_right.bmp");
					//SDL_BlitSurface(ppImage[3], NULL, winSurface, NULL);
					//SDL_UpdateWindowSurface(window);
				}


				else if (InputMgr.isKeyPressed(SDL_SCANCODE_ESCAPE))
				{
					isRunning = false;
				}
				/*
				SDL_BlitSurface(ppImage[testing], NULL, winSurface, NULL);
				SDL_UpdateWindowSurface(window);
				testing = (testing + 1) % 4;

				int bob = 0;
				bob = bob;
				*/

				SDL_BlitSurface(currentSurface, NULL, winSurface, NULL);
				SDL_UpdateWindowSurface(window);
				InputMgr.Update();
				framerateController.FrameEnd();
			}	//GAME LOOP HERE

			//Destroy context and window

			//shader.CleanUp();
			
		//	for (int i = 0; i < 4; i++)
		//	{
			//	SDL_FreeSurface(ppImage[i]);
		//	}
			SDL_FreeSurface(winSurface);
		//	SDL_GL_DeleteContext(context);

			// Destroy our window
			SDL_DestroyWindow(window);

			// Shutdown SDL 2
			SDL_Quit();
		}
	
}