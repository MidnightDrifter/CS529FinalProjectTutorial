#pragma once
#include "GameObject.h"
#include "SpriteBasic.h"
#include "Body.h"
#include "Transform.h"
#include <vector>
class GameObjectManager
{
public:
	GameObjectManager();
	~GameObjectManager();
	void Update();
	GameObject* spawnObject(GAME_OBJECT_TYPE g);



	std::vector<GameObject*> objects;

};

