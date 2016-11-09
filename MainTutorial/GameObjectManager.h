#pragma once
#include "GameObject.h"
#include <vector>
class GameObjectManager
{
public:
	GameObjectManager();
	~GameObjectManager();
	void Update();



	std::vector<GameObject*> objects;

};

