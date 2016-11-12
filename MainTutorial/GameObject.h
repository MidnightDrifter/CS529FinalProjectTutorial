#pragma once
#include <vector>
#include "Component.h"
//#include "SpriteBasic.h"
//#include "Transform.h"
//#include "Controller.h"
//class Component;

enum class GAME_OBJECT_TYPE
{
	PLAYER,
	ASTEROID,
	BULLET,
	NULLTYPE
};

class GameObject
{
public:
	GameObject();
	GameObject(GAME_OBJECT_TYPE t);
	~GameObject();
	//Controller* getController();
	//SpriteBasic* getSprite();
	//Transform* getTransform();
	Component* getComponent(COMPONENT_TYPE c);
	void Update();
	void addComponent(Component* p);
	


private:
	//Controller* controller;
	//SpriteBasic* sprite;
	//Transform* transform;
	std::vector<Component*> components;
	GAME_OBJECT_TYPE type;

};

