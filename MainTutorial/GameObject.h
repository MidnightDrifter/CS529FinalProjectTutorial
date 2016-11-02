#pragma once
#include <vector>
#include "Component.h"
//#include "SpriteBasic.h"
//#include "Transform.h"
//#include "Controller.h"
//class Component;


class GameObject
{
public:
	GameObject();
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

};

