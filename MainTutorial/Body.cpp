#include "Body.h"
#include "PhysicsManager.h"
#include "GameObjectManager.h"
extern GameObjectManager& GameObjMgr;


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

	//accelX = totalForceX*inverseMass;
	//accelY = totalForceY*inverseMass;

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
		Transform* t = static_cast<Transform*>(owner->getComponent(COMPONENT_TYPE::TRANSFORM));
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

	accelX = accelY = totalForceX=totalForceY= 0.f;

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
		fscanf(*fpp, "%f, %f, %f, %f\n", &a->left, &a->right, &a->top, &a->bot);
	}


}


void Body::handleEvent(Event* e)
{
	if (e->eType == EVENT_TYPE::COLLISION && (this->owner->getType() == GAME_OBJECT_TYPE::ALIEN || this->owner->getType()==GAME_OBJECT_TYPE::ASTEROID || this->owner->getType() == GAME_OBJECT_TYPE::SQUARE_MOVER))
	{
		CollisionEvent* c = static_cast<CollisionEvent*>(e);
		GameObject* me = NULL;
		GameObject* other = NULL;
		if ((c->pObject1) == this->owner)
		{
			me = c->pObject1;
			other = c->pObject2;
		}

		else
		{
			me = c->pObject2;
			other = c->pObject1;
		}

		if (other->getType() == GAME_OBJECT_TYPE::BULLET || other->getType() == GAME_OBJECT_TYPE::MISSILE)
		{
			int size = GameObjMgr.objects.size();
			for (int i = 0; i < size; i++)
			{
				if (GameObjMgr.objects[i] == me || GameObjMgr.objects[i] == other)
				{
					GameObjMgr.objects.erase(GameObjMgr.objects.begin() + i);
					size = GameObjMgr.objects.size();
					i = 0;
				}
			}
			//delete other;
		}
			


	}
}