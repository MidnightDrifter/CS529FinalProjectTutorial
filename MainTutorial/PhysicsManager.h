#pragma once
#include "GameObject.h"
#include "GameObjectManager.h"
//#include "FramerateController.h"
#include "Body.h"
class PhysicsManager
{
public:
	PhysicsManager();
	~PhysicsManager();
	void Integrate(float deltaTime);

private:
	float GRAVITY = 1.f;

};

