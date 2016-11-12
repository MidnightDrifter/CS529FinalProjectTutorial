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
		obj = new GameObject(GAME_OBJECT_TYPE::BULLET);
		Body b = Body();
		SpriteBasic sb = SpriteBasic("Bullet.bmp");
		Transform t = Transform();
		




		obj->addComponent(&b);
		obj->addComponent(&sb);
		obj->addComponent(&t);
	}

	else if (g == GAME_OBJECT_TYPE::ASTEROID)
	{

	}

	else if (g == GAME_OBJECT_TYPE::PLAYER)
	{

	}
	if (obj)
	{
		objects.push_back(obj);
	}
	return obj;
}
