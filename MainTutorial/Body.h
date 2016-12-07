#pragma once
#include "Component.h"
#include "Transform.h"
#include "GameObject.h"
#include "CollisionManager.h"
#include <set>
class Body :
	public Component
{
public:
	Body();
	~Body();

	void Update(void);
	void Serialize(FILE **fpp);

	void Integrate(float deltaTime, float gravity);  //Maybe not useful for me because asteroids
	void handleEvent(Event* e);

//private:
	float currPosX, currPosY;
	float prevPosX, prevPosY;
	float velX, velY;
	float accelX, accelY;
	float totalForceX, totalForceY;
	float mass, inverseMass;
	Shape* shape;

};

