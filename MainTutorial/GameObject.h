#pragma once
#include <vector>
#include "Component.h"
//#include "SpriteBasic.h"
//#include "Transform.h"
//#include "Controller.h"
//class Component;
class Event;
enum class GAME_OBJECT_TYPE
{
	PLAYER,
	ASTEROID,
	BULLET,
	ALIEN,
	MISSILE,
	NULLTYPE,
	SQUARE_MOVER
	NUM
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
	GAME_OBJECT_TYPE getType() const { return type; }
	void HandleEvent(Event* e);
	void setType(GAME_OBJECT_TYPE t) { type = t; }


private:
	//Controller* controller;
	//SpriteBasic* sprite;
	//Transform* transform;
	std::vector<Component*> components;
	GAME_OBJECT_TYPE type;

};

