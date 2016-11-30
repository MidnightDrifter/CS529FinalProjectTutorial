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
#include <Windows.h>
#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")
//#pragma comment (lib, "glew32.lib")
//#pragma comment (lib, "glfw3.lib")
//# define GL3_PROTOTYPES 1
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
//SDL_Surface* winSurface;
SDL_GLContext context;
InputManager& InputMgr = InputManager();
FramerateController& framerateController = FramerateController(30);
ResourceManager& ResourceMgr = ResourceManager();
GameObjectManager& GameObjMgr = GameObjectManager();
PhysicsManager& PhysicsMgr = PhysicsManager();
CollisionManager& CollisionMgr = CollisionManager();
EventManager& EventMgr = EventManager();
//SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

GLint globalShaderID;


void LoadShaders(void)
{
	//Step 1 - make program
	globalShaderID = glCreateProgram();

	//Step 2 - make vertex & pixel shaders, create + compile

	//Vertetx shader

	const char * vertexShaderCode = "//uniform mat4 transform;					\
									 attribute vec4 aPosition;					\
									 attribute vec4 aColor;						\
								//	attribute vec2 aTextureCoordinates;			\
								//	varying vec2 vTextureCoordinates;			\
									  varying vec4 vColor;						\
									  void main()								\
									{											\
									//vec4 worldPos = transform * aPosition;		\
									vColor = aColor;							\
									//vTextureCoordinates = aTextureCoordinates;	\
								    gl_Position = aPosition;						\
									}";




	const char* fragmentShaderCode = "	varying vec4 vColor;												\
									//	varying vec2 vTextureCoordinates;									\
									//	uniform sampler2D testTexture;										\
									  void main()															\
									 {																		\
									gl_FragColor = vColor;													\
									gl_FragColor.r = 1.0; \
								//	glFragColor.xyz = texture2D(testTexture,vTextureCoordinates).xyz;		\
									} ";

	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderID,1, &vertexShaderCode, NULL);
	glCompileShader(vertexShaderID);

	GLint status;
	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &status);
	if (status == GL_TRUE)
	{
		glAttachShader(globalShaderID, vertexShaderID);
	}

	GLuint fragShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShaderID, 1, &fragmentShaderCode, NULL);
	glCompileShader(fragShaderID);

	glGetShaderiv(fragShaderID, GL_COMPILE_STATUS, &status);
		if (status == GL_TRUE)
		{
			glAttachShader(globalShaderID, fragShaderID);
		}

		//3)  Link program
		glLinkProgram(globalShaderID);
		//4)  Use program
		glUseProgram(globalShaderID);

}













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


//	ResourceMgr.loadSurface("Resources\\darkpursuit.bmp");
//	ResourceMgr.loadSurface("Resources\\dark_pursuit_small_down.bmp");
//	ResourceMgr.loadSurface("Resources\\dark_pursuit_small_left.bmp");
//	ResourceMgr.loadSurface("Resources\\dark_pursuit_small_right.bmp");

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
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);


		window = SDL_CreateWindow("Test Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

		// Check that everything worked out okay
		if (!window)
		{
			std::cout << "Unable to create window\n";
			//CheckSDLError(__LINE__);
			return false;
		}
		
		context = SDL_GL_CreateContext(window);
		
		if (glewInit() != GLEW_OK)
		{
			printf("GLEW intitialization failed.\n");
			return false;
		}


		//Ensure OpenGL 2.0 is supported
		if(!GLEW_VERSION_2_0)
		{ return false; }

		LoadShaders();


		GLuint bufferPosition, bufferColors, bufferTexture;
		glGenBuffers(1, &bufferPosition);  //Position buffer
		glGenBuffers(1, &bufferColors);  //Color buffer
		glGenBuffers(1, &bufferTexture);

		int vertexNum = 3;   //Number of vertices
		int coordsPerPosition = 3;    // (x,y,z)
		int colorsPerPosition = 4;   //4 vals per color, RGBA
		int coordsPerTextureCoord = 2;

		int posBufferSize = vertexNum * coordsPerPosition * sizeof(GLfloat);
		int colorBufferSize = vertexNum * colorsPerPosition * sizeof(GLfloat);
		int textureCoordBufferSize = vertexNum * coordsPerTextureCoord * sizeof(GLfloat);  // ????

		GLfloat* pPosition = new GLfloat[vertexNum * coordsPerPosition];
		GLfloat* pColor = new GLfloat[vertexNum * colorsPerPosition];
		GLfloat* pTextureCoords = new GLfloat[vertexNum * coordsPerTextureCoord];


		//glVertex2f(-0.5f, -0.5f);  glColor3f(1.0f, 0.0f, 0.f);  //Vertex pos, vertex color -- colors are normalized from 0-1
		//glVertex2f(0.5f, -0.5f);  glColor3f(0.0f, 01.f, 0.f);
		//glVertex2f(0.5f, 0.5f);  glColor3f(0.f, 0.f, 01.f);


		pPosition[0] = -0.5f;  pPosition[1] = -0.5f;  pPosition[2] = 0.f;   //Vertex 1  (-.5, -.5, 0)
		pColor[0] = 1.f;  pColor[1] = 0.f;  pColor[2] = 0.f;  pColor[3] = 1.f;
		pTextureCoords[0] = 0.f;  pTextureCoords[1] = 1.f;



		pPosition[3] = 0.5f;  pPosition[4] = -0.5f;  pPosition[5] = 0.f;   //Vertex 2  (.5, -.5, 0)
		pColor[4] = 0.f;  pColor[5] = 1.f;  pColor[6] = 0.f;  pColor[7] = 1.f;
		pTextureCoords[2] = 1.f;  pTextureCoords[3] = 1.f;

		pPosition[6] = 0.5f;  pPosition[7] = 0.5f;  pPosition[8] = 0.f;   //Vertex 3  (.5, .5, 0)
		pColor[8] = 0.f;  pColor[9] = 0.f;  pColor[10] =1.f;  pColor[11] = 1.f;
		pTextureCoords[4] = 0.5f; pTextureCoords[5] = 0.f;
		//Drawing a triangle--texture is square, points of triangle at: bot left, bot right, top middle
		//Tex coords normalized so coords are:  (0,1) (1,1), (0.5,0)



		//Pass position buffer to OpenGL, graphics card
		glBindBuffer(GL_ARRAY_BUFFER, bufferPosition);   //Specify buffer
		glBufferData(GL_ARRAY_BUFFER, posBufferSize, pPosition, GL_STATIC_DRAW);  //Specify data inside buffer--what kind of format, size of buffer, pointer to data, what to do with the data
		glBindBuffer(GL_ARRAY_BUFFER, 0);  //Clear what buffer you're bound to

		glBindBuffer(GL_ARRAY_BUFFER, bufferColors);  //Pass color buffer to OpenGl, graphics card
		glBufferData(GL_ARRAY_BUFFER, colorBufferSize, pColor, GL_STATIC_DRAW);  //Specify data inside buffer--what kind of format, size of buffer, pointer to data, what to do with the data
		glBindBuffer(GL_ARRAY_BUFFER, 0);   //Clear what buffer you're bound to

		//glBindBuffer(GL_ARRAY_BUFFER, bufferTexture );
		//glBufferData(GL_ARRAY_BUFFER, textureCoordBufferSize, pTextureCoords, GL_STATIC_DRAW);
		//glBindBuffer(GL_ARRAY_BUFFER, 0);


		glFinish();  //Have everything wait until the drawing is done

//Get rid of buffers, send to graphics card already!
		delete[] pPosition;
		delete[] pColor;
		delete[] pTextureCoords;

		//winSurface = SDL_GetWindowSurface(window);
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


		//Generating texture(s)

/*
		ULONG_PTR mGdiPlusToken;
		Gdiplus::GdiplusStartupInput d;
		Gdiplus::GdiplusStartup(&mGdiPlusToken, &d,NULL);

		GLuint texID;
		Gdiplus::Bitmap bmp(L"Resources//ship.bmp");  //May need to remove the 'L'
		Gdiplus::Rect rect(0, 0, bmp.GetWidth(), bmp.GetHeight());
		Gdiplus::BitmapData data;
		bmp.LockBits(&rect, Gdiplus::ImageLockModeRead, PixelFormat32bppARGB, &data);
		glGenTextures(1, &texID);

		//Generated texture

		//Bind created texture
		glBindTexture(GL_TEXTURE_2D, texID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, data.Width, data.Height,0,GL_BGRA_EXT,GL_UNSIGNED_BYTE, data.Scan0 );

			bmp.UnlockBits(&data);

*/

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

				//for (GameObject* g : GameObjMgr.objects)
				int size = GameObjMgr.objects.size();
				for(int i=0;i<size;i++)
				{
					GameObjMgr.objects.at(i)->Update();
					size = GameObjMgr.objects.size();
				//	g->Update();

				}




//				SDL_FillRect(winSurface, NULL, 0);
				

				// 512 x 365



				for (GameObject* g : GameObjMgr.objects)
				{
					SpriteBasic* s = (SpriteBasic*)g->getComponent(COMPONENT_TYPE::SPRITE);
					Transform* t = (Transform*)g->getComponent(COMPONENT_TYPE::TRANSFORM);
					if (t != NULL && s != NULL)
					{
						SDL_Rect destRect;
						destRect.x = t->getX();
						destRect.y = t->getY();
						destRect.w = 512;
						destRect.h = 365;
					//	destRect.x = 100.f;
					//	destRect.y = 100.f;


						//SDL_BlitSurface(s->getSprite(), NULL, winSurface, &destRect);
					}
					
				}
				//SDL_UpdateWindowSurface(window);
				glClearColor(0.f, 1.f, 1.f, 0.f);  //Default background color
				glClear(GL_COLOR_BUFFER_BIT);  //Clear framebuffer



				//DRAW A TRIANGLE WHEEEEE
				//Fixed pipeline - OpenGL try 1
				//glBegin(GL_TRIANGLES);
				//glVertex2f(-0.5f, -0.5f);  glColor3f(1.0f, 0.0f, 0.f);  //Vertex pos, vertex color -- colors are normalized from 0-1
				//glVertex2f(0.5f, -0.5f);  glColor3f(0.0f, 01.f, 0.f);
				//glVertex2f(0.5f, 0.5f);  glColor3f(0.f, 0.f, 01.f);

				//Without any perspective / Projection matrix, these 0-1 values from the vertices will correspond to the aspect ratio of the screen

				//This set of vertices--directly set--is fixed pipeline.  No shading.

				//glEnd();

				//Fixed pipeline w/ VBO
				//OpenGL try 2
				
				/*
				glEnableClientState(GL_VERTEX_ARRAY);
				glEnableClientState(GL_COLOR_ARRAY);


				glBindBuffer(GL_ARRAY_BUFFER, bufferPosition);
				glVertexPointer(coordsPerPosition, GL_FLOAT, coordsPerPosition * sizeof(GLfloat), NULL);
				glBindBuffer(GL_ARRAY_BUFFER, 0);

				glBindBuffer(GL_ARRAY_BUFFER, bufferColors);
				glVertexPointer(colorsPerPosition, GL_FLOAT, colorsPerPosition * sizeof(GLfloat), NULL);
				glBindBuffer(GL_ARRAY_BUFFER, 0);


			//	glDrawArrays(GL_TRIANGLES, 0, vertexNum);


				glDisableClientState(GL_VERTEX_ARRAY);
				glDisableClientState( GL_COLOR_ARRAY);
				*/


				int posHandle, colorHandle, matrixHandle, textureHandle, texCoordHandle;
				posHandle = glGetAttribLocation(globalShaderID, "aPosition");
				glEnableVertexAttribArray(posHandle);
				glBindBuffer(GL_ARRAY_BUFFER, bufferPosition);
				glVertexAttribPointer(posHandle, coordsPerPosition,GL_FLOAT,false,0,NULL);
							
				colorHandle = glGetAttribLocation(globalShaderID, "aColor");
				glEnableVertexAttribArray(colorHandle);
				glBindBuffer(GL_ARRAY_BUFFER, bufferColors);
				glVertexAttribPointer(colorHandle, colorsPerPosition, GL_FLOAT, false, 0, NULL);
				
				matrixHandle = glGetUniformLocation(globalShaderID, "transform");
				GLfloat mat[4][4] = { 0 };
				mat[0][0] = mat[1][1] = mat[2][2] = mat[3][3] = 1.f;
				glUniformMatrix4fv( matrixHandle, 1, false, (const GLfloat *)mat);
				/*
				texCoordHandle = glGetAttribLocation(globalShaderID, "aTextureCoordinates");
				glEnableVertexAttribArray(texCoordHandle);
				glBindBuffer(GL_ARRAY_BUFFER, bufferTexture);
				glVertexAttribPointer(texCoordHandle, coordsPerTextureCoord, GL_FLOAT, false, 0, 0);


				textureHandle = glGetUniformLocation(globalShaderID, "testTexture");
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, texID);
				glUniform1i(textureHandle, 0);
				*/



				glDrawArrays(GL_TRIANGLES, 0, vertexNum);

			//	glDisableVertexAttribArray(texCoordHandle);
				glDisableVertexAttribArray(posHandle);
				glDisableVertexAttribArray(colorHandle);

				SDL_GL_SwapWindow(window);  //Update the window
				framerateController.FrameEnd();
			}	//GAME LOOP HERE

			//Destroy context and window

			//shader.CleanUp();
			
		//	for (int i = 0; i < 4; i++)
		//	{
			//	SDL_FreeSurface(ppImage[i]);
		//	}

			//Gdiplus::GdiplusShutdown(mGdiPlusToken);
			SDL_GL_DeleteContext(context);
		//	SDL_FreeSurface(winSurface);
		//	SDL_GL_DeleteContext(context);

			// Destroy our window
			SDL_DestroyWindow(window);

			// Shutdown SDL 2
			SDL_Quit();
		}
	
}