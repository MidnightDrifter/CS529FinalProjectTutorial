#pragma once
#include "GameObject.h"
#include "SpriteBasic.h"
#include "Sprite.h"
#include "Body.h"
#include "Transform.h"
#include "Controller.h"
#include "Homing.h"
#include "SquareMover.h"
#include <vector>
class GameObjectManager
{
public:
	GameObjectManager();
	~GameObjectManager();
	void Update();
	GameObject* spawnObject(GAME_OBJECT_TYPE g);
	GameObject* LoadObject(const char* c);

	void LoadLevel(const char* c);

	std::vector<GameObject*> objects;

};

