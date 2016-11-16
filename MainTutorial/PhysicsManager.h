#pragma once
#include "GameObject.h"
#include "GameObjectManager.h"
//#include "FramerateController.h"
#include "Body.h"
#include "EventManager.h"
#include <stdio.h>
class CollisionEvent : public Event
{
public:
	CollisionEvent() : Event(EVENT_TYPE::COLLISION), pObject1(NULL), pObject2(NULL) {}
	~CollisionEvent() {}

	GameObject* pObject1;
	GameObject* pObject2;
};


class PhysicsManager
{
public:
	PhysicsManager();
	~PhysicsManager();
	void Integrate(float deltaTime);

private:
	float GRAVITY = 1.f;

};

