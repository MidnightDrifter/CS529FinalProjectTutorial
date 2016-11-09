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
