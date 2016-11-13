#pragma once
#include "Component.h"
class Homing :
	public Component
{
public:
	Homing() : target(NULL), Component(COMPONENT_TYPE::HOMING) {}
	Homing(GameObject* g) : target(g), Component(COMPONENT_TYPE::HOMING){}
	void Update();
	~Homing();


	GameObject* target;
};

