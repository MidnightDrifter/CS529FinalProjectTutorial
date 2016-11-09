#include "Body.h"



Body::Body():  Component(COMPONENT_TYPE::BODY), currPosX(0.f), currPosY(0.f), prevPosX(0.f), prevPosY(0.f), velX(0.f), velY(0.f), accelX(0.f), accelY(0.f), mass(0.f), inverseMass(0.f)
{
}



Body::~Body()
{
	if (NULL !=shape)
	{
		delete shape;
	}
}



void Body::Integrate(float deltaTime, float gravity)
{

	if (owner)
	{
		Transform* t = (Transform*)owner->getComponent(COMPONENT_TYPE::TRANSFORM);
		if (t)
		{
			currPosX = t->getX();
			currPosY = t->getY();

		}
	}



	//Save positions
	prevPosX = currPosX;
	prevPosY = currPosY;

	//Compute accel.
	//totalForceY += gravity;  //Irrelevant for me b/c Asteroids

	accelX = totalForceX*inverseMass;
	accelY = totalForceY*inverseMass;

	//Compute vel.
	velX += accelX * deltaTime;
	velY += accelY*deltaTime;

	//Compute pos.
	currPosX += velX*deltaTime;
	currPosY += velY*deltaTime;

	totalForceX = totalForceY = 0.f;


	//Update transform component
	if (owner)
	{
		Transform* t = (Transform*)owner->getComponent(COMPONENT_TYPE::TRANSFORM);
		if (t)
		{
			t->setX(currPosX);
			t->setY(currPosY);
		}
	}

	//

}

void Body::Update()
{

}

void Body::Serialize(FILE** fpp)
{
	fscanf(*fpp, "%f\n", &mass);
	if (0.0f != mass)
	{
		inverseMass = 1.f / mass;
	}
	else
	{
		inverseMass = 0.f;
	}



	char shapeType[256];
	memset(shapeType, 0, 256 * sizeof(char));

	fscanf(*fpp, "%255s\n", shapeType, sizeof(shape));

	if (0 == strcmp(shapeType, "Circle"))
	{
		shape = new ShapeCircle();
		shape->bodyOwner = this;
		ShapeCircle* c = (ShapeCircle*)shape;
		fscanf(*fpp, "%f\n", &c->radius);
	}


	if (0 == strcmp(shapeType, "AABB"))
	{
		shape = new ShapeAABB();
		shape->bodyOwner = this;
		ShapeAABB* a = (ShapeAABB*)shape;
		fscanf(*fpp, "%f %f %f %f\n", &a->left, &a->right, &a->top, &a->bot);
	}


}
