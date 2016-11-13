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


		obj = LoadObject("Bullet.txt");

	}

	else if (g == GAME_OBJECT_TYPE::ASTEROID)
	{
		obj = LoadObject("Asteroid.txt");
	}

	else if (g == GAME_OBJECT_TYPE::PLAYER)
	{
		obj = LoadObject("Player.txt");
	}
	else if (g == GAME_OBJECT_TYPE::ALIEN)
	{
		obj = LoadObject("Alien.txt");
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
			h->serialize(&fp);
			obj->addComponent();
		}
		/*  AI Component thing
		else if (0 == name.compare(""))
		{

		}
		*/
	}
	fclose(fp);

	return obj;
}



