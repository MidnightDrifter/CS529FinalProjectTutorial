#include "GameObjectManager.h"



GameObjectManager::GameObjectManager() : objects()
{
}


GameObjectManager::~GameObjectManager()
{
	for (auto i = objects.begin(); i != objects.end(); i++)
	{
		delete *i;
	}

	objects.clear();
}

void GameObjectManager::Update()
{
	for (auto i = objects.begin(); i != objects.end(); i++)
	{
		(*i)->Update();
	}
}


void GameObjectManager::LoadLevel(const char* s)
{
	GameObject* obj = NULL;
	FILE* fp;
	errno_t err = fopen_s(&fp,s, "r");
	if (err)
	{
		printf("Error opening file, terminating.\n");
		exit(-1);
	}
	char c[100];
	while (!feof(fp))
	{
		memset(c, 0, sizeof(char) * 100);
		fscanf(fp, "%s\n", c);


		if (0==strcmp(c, "Asteroid1.txt"))
		{
			obj = LoadObject("TextFiles\\Asteroid1SDLVer.txt");
			obj->setType(GAME_OBJECT_TYPE::ASTEROID);
		}

		else if (0 == strcmp(c, "Asteroid2.txt"))
		{
			obj = LoadObject("TextFiles\\Asteroid2SDLVer.txt");
			obj->setType(GAME_OBJECT_TYPE::ASTEROID);
		}
		else if (0 == strcmp(c, "Asteroid3.txt"))
		{
			obj = LoadObject("TextFiles\\Asteroid3SDLVer.txt");
			obj->setType(GAME_OBJECT_TYPE::ASTEROID);
		}
		else if (0 == strcmp(c, "Alien.txt"))
		{
			obj = LoadObject("TextFiles\\AlienSDLVer.txt");
			obj->setType(GAME_OBJECT_TYPE::ALIEN);

		}

		else if (0 == strcmp(c, "Player.txt"))
		{
			obj = LoadObject("TextFiles\\PlayerSDLVer.txt");
			obj->setType(GAME_OBJECT_TYPE::PLAYER);
		}

		else if (0 == strcmp(c, "Transform") && obj != NULL)
		{
			float x, y;
			fscanf(fp,"%f %f\n", &x, &y);
			Transform* t = static_cast<Transform*>(obj->getComponent(COMPONENT_TYPE::TRANSFORM));
			t->setX(x);
			t->setY(y);
			
		}

		else if (0 == strcmp(c, "SquareMover.txt"))
		{
			obj=LoadObject("TextFiles\\SquareMover.txt");
			obj->setType(GAME_OBJECT_TYPE::SQUARE_MOVER);
		}

		else if (0 == strcmp(c, "DONE") && obj != NULL)
		{
			objects.push_back(obj);
		}
	}
	fclose(fp);
}

GameObject* GameObjectManager::spawnObject(GAME_OBJECT_TYPE g)
{
	GameObject* obj = NULL;// new GameObject();
	if (g == GAME_OBJECT_TYPE::BULLET)
	{
		//obj = new GameObject(GAME_OBJECT_TYPE::BULLET);
		//Body b = Body();
		//SpriteBasic sb = SpriteBasic("Bullet.bmp");
		//Transform t = Transform();
		//




		//obj->addComponent(&b);
		//obj->addComponent(&sb);
		//obj->addComponent(&t);


		obj = LoadObject("TextFiles\\BulletSDLVer.txt");
		obj->setType(GAME_OBJECT_TYPE::BULLET);
	}

	else if (g == GAME_OBJECT_TYPE::ASTEROID)
	{
		obj = LoadObject("TextFiles\\AsteroidSDLVer.txt");
		obj->setType(GAME_OBJECT_TYPE::ASTEROID);
	}

	else if (g == GAME_OBJECT_TYPE::PLAYER)
	{
		obj = LoadObject("TextFiles\\PlayerSDLVer.txt");
		obj->setType(GAME_OBJECT_TYPE::PLAYER);
	}
	else if (g == GAME_OBJECT_TYPE::ALIEN)
	{
		obj = LoadObject("TextFiles\\AlienSDLVer.txt");
		obj->setType(GAME_OBJECT_TYPE::ALIEN);
	}

	else if (g == GAME_OBJECT_TYPE::MISSILE)
	{
		obj = LoadObject("TextFiles\\HomingMissileSDLVer.txt");
		obj->setType(GAME_OBJECT_TYPE::MISSILE);
	}
	if (obj)
	{
		objects.push_back(obj);
	}
	return obj;
}





GameObject* GameObjectManager::LoadObject(const char *pFilename)
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
		if (0 == strcmp(name, "Transform"))
		{
			Transform* t = new Transform();
			t->Serialize(&fp);

			obj->addComponent(t);
		}

		else if (0 == strcmp("Sprite", name))
		{
			SpriteBasic* t = new SpriteBasic();
			//Sprite* t = new Sprite();
			t->Serialize(&fp);
			obj->addComponent(t);
		}

		else if (0 == strcmp(name, "Controller"))
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

		else if (0 == strcmp(name, "Homing"))
		{
			Homing* h = new Homing();
			h->Serialize(&fp);
			obj->addComponent(h);
		}
		  //AI Component thing
		else if (0 == strcmp(name,"SquareMover"))
		{
			SquareMover* s = new SquareMover();
			s->Serialize(&fp);
			obj->addComponent(s);
		}
		
	}
	fclose(fp);

	return obj;
}



