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
#include "GameObject.h"
#include "Transform.h"
#include "SpriteBasic.h"
#include "Controller.h"
#include "Body.h"
#include "GameObjectManager.h"
#include "PhysicsManager.h"
#include "CollisionManager.h"
#include "EventManager.h"
#pragma comment (lib, "glew32.lib")
#pragma comment (lib, "glfw3.lib")
# define GL3_PROTOTYPES 1
const int SCREEN_HEIGHT = 800;
const int SCREEN_WIDTH = 1200;
const int OPEN_GL_MAJOR_VERSION = 3; //OpenGL version 3.x
const int OPEN_GL_MINOR_VERSION = 2;  // OpenGL version x.2
const int USE_DOUBLE_BUFFER = 1;  //1 = use double buffering
const float GRAVITY = 0.f;

const float INSTRUCTION_POS_X = 0.f;
const float INSTRUCTION_POS_Y = -200.f;


const float INSTRUCTION_WIDTH = 1.f;
const float INSTRUCTION_HEIGHT = 1.f;  //Update & change these based on the size of the .bmp I make
//Woo
int test;
//Shader shader;
SDL_Window* window;
SDL_Surface* surface;
SDL_Surface* winSurface;
SDL_GLContext context;
InputManager& InputMgr = InputManager();
FramerateController& framerateController = FramerateController(30);
ResourceManager& ResourceMgr = ResourceManager();
GameObjectManager& GameObjMgr = GameObjectManager();
PhysicsManager& PhysicsMgr = PhysicsManager();
CollisionManager& CollisionMgr = CollisionManager();
EventManager& EventMgr = EventManager();
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



GameObject* LoadObject(const char *pFilename)
{
	GameObject* obj = new GameObject();
	FILE* fp;
	errno_t err = fopen_s(&fp, pFilename, "r");
	if (err)
	{
		printf("Error opening file, terminating.\n");
		exit(-1);
	}
	char name[100];
		while (!feof(fp))
		{
			memset(name, 0, sizeof(char) * 100);
			fscanf(fp, "%s\n", name);
			if (0==strcmp(name,"Transform"))
			{
				Transform* t = new Transform();
				t->Serialize(&fp);
				
				obj->addComponent(t);
			}

			else if (0==strcmp("Sprite",name))
			{
				SpriteBasic* t = new SpriteBasic();
				t->Serialize(&fp);
				obj->addComponent(t);
			}

			else if (0 == strcmp(name,"Controller"))
			{
				Controller* t = new Controller();
				t->Serialize(&fp);
				obj->addComponent(t);

			}

			else if (0 == strcmp(name, "Body"))
			{
				Body* t = new Body();
				t->Serialize(&fp);
				obj->addComponent(t);
			}
/*  AI Component thing
			else if (0 == name.compare(""))
			{

			}

		}
		fclose(fp);
		GameObjMgr.objects.push_back(obj);
		return obj;
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


	ResourceMgr.loadSurface("Resources\\darkpursuit.bmp");
	ResourceMgr.loadSurface("Resources\\dark_pursuit_small_down.bmp");
	ResourceMgr.loadSurface("Resources\\dark_pursuit_small_left.bmp");
	ResourceMgr.loadSurface("Resources\\dark_pursuit_small_right.bmp");

	//SDL_Surface* ppImage[4] = { NULL, NULL, NULL, NULL };

	//ppImage[0] = SDL_LoadBMP("..\\Resources\\darkpursuit.bmp");
	//ppImage[0] = SDL_LoadBMP("Resources\\darkpursuit.bmp");
	//ppImage[1] = SDL_LoadBMP("Resources\\dark_pursuit_small_down.bmp");
	//ppImage[2] = SDL_LoadBMP("Resources\\dark_pursuit_small_left.bmp");
	//ppImage[3] = SDL_LoadBMP("Resources\\dark_pursuit_small_right.bmp");
//	GameObject * testObject = GameObjMgr.LoadObject("TestSerializerPlayerChar.txt");
//	Transform* testTransform = static_cast<Transform*>(testObject->getComponent(COMPONENT_TYPE::TRANSFORM));
//	SpriteBasic* testSprite = static_cast<SpriteBasic*>(testObject->getComponent(COMPONENT_TYPE::SPRITE));
//	Controller* testController = static_cast<Controller*>(testObject->getComponent(COMPONENT_TYPE::CONTROLLER));

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
		/*
		SDL_Surface * currentSurface = ResourceMgr.loadSurface("Resources\\darkpursuit.bmp");
		SDL_BlitSurface(currentSurface, NULL, winSurface, NULL);
		SDL_UpdateWindowSurface(window);
		
		*/
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


			GameObject* startingObject = GameObjMgr.spawnObject(GAME_OBJECT_TYPE::PLAYER);

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






				/*

				if (InputMgr.isKeyPressed(SDL_SCANCODE_UP))
				{
					currentSurface = ResourceMgr.loadSurface("Resources\\darkpursuit.bmp");
					//SDL_BlitSurface(ppImage[0], NULL, winSurface, NULL);
					//SDL_UpdateWindowSurface(window);
				}

				else if (InputMgr.isKeyPressed(SDL_SCANCODE_DOWN))
				{

					currentSurface = ResourceMgr.loadSurface("Resources\\dark_pursuit_small_down.bmp");
					//SDL_BlitSurface(ppImage[1], NULL, winSurface, NULL);
					//SDL_UpdateWindowSurface(window);
				}

				else if (InputMgr.isKeyPressed(SDL_SCANCODE_LEFT))
				{
					currentSurface = ResourceMgr.loadSurface("Resources\\dark_pursuit_small_left.bmp");
					//SDL_BlitSurface(ppImage[2], NULL, winSurface, NULL);
					//SDL_UpdateWindowSurface(window);
				}

				else if (InputMgr.isKeyPressed(SDL_SCANCODE_RIGHT))
				{
					currentSurface = ResourceMgr.loadSurface("Resources\\dark_pursuit_small_right.bmp");
					//SDL_BlitSurface(ppImage[3], NULL, winSurface, NULL);
					//SDL_UpdateWindowSurface(window);
				}


				else if (InputMgr.isKeyPressed(SDL_SCANCODE_ESCAPE))
				{
					isRunning = false;
				}
				
				SDL_BlitSurface(ppImage[testing], NULL, winSurface, NULL);
				SDL_UpdateWindowSurface(window);
				testing = (testing + 1) % 4;

				int bob = 0;
				bob = bob;
				*/

			//	SDL_BlitSurface(currentSurface, NULL, winSurface, NULL);
			
				InputMgr.Update();

				float frametime = (float)(framerateController.getFrameTime()) / 1000.f;
				PhysicsMgr.Integrate(frametime/1000.f);
				EventMgr.Update(frametime);

				for (GameObject* g : GameObjMgr.objects)
				{
				
					g->Update();

				}




				SDL_FillRect(winSurface, NULL, 0);
				SDL_Rect destRect;

				// 512 x 365
				destRect.w = 512;
				destRect.h = 365;


				for (GameObject* g : GameObjMgr.objects)
				{
					SpriteBasic* s = (SpriteBasic*)g->getComponent(COMPONENT_TYPE::SPRITE);
					Transform* t = (Transform*)g->getComponent(COMPONENT_TYPE::TRANSFORM);
					if (t != NULL && s != NULL)
					{
						destRect.x = t->getX();
						destRect.y = t->getY();
					//	destRect.x = 100.f;
					//	destRect.y = 100.f;


						SDL_BlitSurface(s->getSprite(), NULL, winSurface, &destRect);
					}
					
				}
				SDL_UpdateWindowSurface(window);

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