#pragma once
#include "GameObject.h"
#include <vector>
class GameObjectManager
{
public:
	GameObjectManager();
	~GameObjectManager();
	void Update();


private:
	std::vector<GameObject*> objects;

};

