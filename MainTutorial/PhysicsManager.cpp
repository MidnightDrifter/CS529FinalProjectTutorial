#include "PhysicsManager.h"
#include "CollisionManager.h"
#include "FramerateController.h"
#include "Transform.h"
#include <algorithm>
extern GameObjectManager& GameObjMgr;
extern FramerateController& framerateController;
extern CollisionManager& CollisionMgr;
extern GameObject* player;
#define MY_PI  3.14159265358979323846f 
#define MAX_HOMING_ROTATION_SPEED MY_PI/2.f
#define MISSILE_SPEED 150.f;
#define ALIEN_SPEED MISSILE_SPEED/2.f
PhysicsManager::PhysicsManager()
{
}


PhysicsManager::~PhysicsManager()
{
}

void PhysicsManager::Integrate(float deltaTime)
{
	for (GameObject* g : GameObjMgr.objects)
	{
		Body *pBody = (Body*)g->getComponent(COMPONENT_TYPE::BODY);
		if (pBody)
		{
			pBody->Integrate(deltaTime, GRAVITY);
		}




	}


	CollisionMgr.Reset();

	//Loop through objects
	
		//Find obj1 that has a body component
		//Find obj2 that has a body component
		//Check for collision between shape of body1 and shape of body2

		unsigned int numObjects = GameObjMgr.objects.size();

		for (int i=0;i<numObjects;i++)// : GameObjMgr.objects)
		{
			Body* body1 = (Body*)GameObjMgr.objects.at(i)->getComponent(COMPONENT_TYPE::BODY);// a->getComponent(COMPONENT_TYPE::BODY);
			if (NULL != body1)
			{
				for (int j = i + 1; j < numObjects; j++)
				{
					Body* body2 = (Body*)GameObjMgr.objects.at(j)->getComponent(COMPONENT_TYPE::BODY);
				
					if (NULL != body2)
					{
						CollisionMgr.CheckCollisionGenerateContacts(body1->shape, body1->currPosX, body1->currPosY, body2->shape, body2->currPosX, body2->currPosY);
					}
				}

			}
		}

		for (auto a : CollisionMgr.contacts)
		{
			CollisionEvent c;
			c.pObject1 = a->bodiesColliding[0]->owner;
			c.pObject2 = a->bodiesColliding[1]->owner;

			a->bodiesColliding[0]->owner->HandleEvent(&c);
			a->bodiesColliding[1]->owner->HandleEvent(&c);
		}


		//Commit changes from physics -> transform	
		for (GameObject* g : GameObjMgr.objects)
		{
			Body *pBody = (Body*)g->getComponent(COMPONENT_TYPE::BODY);
			Homing* h = (Homing*)g->getComponent(COMPONENT_TYPE::HOMING);
			
			if (NULL != pBody)
			{
				Transform *pTransform = (Transform*)g->getComponent(COMPONENT_TYPE::TRANSFORM);
				//pTransform->Integrate(deltaTime *0.0
				pTransform->setX(pBody->currPosX);
				pTransform->setY(pBody->currPosY);


				if (NULL != h)
				{
					//

					if (NULL == h->target)
					{
						if (g->getType() == GAME_OBJECT_TYPE::MISSILE)
						{

							for (GameObject* temp : GameObjMgr.objects)
							{
								if (NULL != temp && (temp->getType() == GAME_OBJECT_TYPE::ALIEN || temp->getType() == GAME_OBJECT_TYPE::ASTEROID))
								{
									h->target = temp;
									break;
								}
							}
						}

						else if (g->getType() == GAME_OBJECT_TYPE::ALIEN)
						{
							h->target = player;
						}

					}
				}

				if (h != NULL)
				{
					Transform* targetTransform = static_cast<Transform*>(h->target->getComponent(COMPONENT_TYPE::TRANSFORM));
					Transform* t = (Transform*)g->getComponent(COMPONENT_TYPE::TRANSFORM);
					Vector2D myVel, normal, targetVec, out;
					Vector2DSet(&myVel, pBody->velX, pBody->velY);
					Vector2DSet(&normal, myVel.y * -1, myVel.x);
					Vector2DSet(&targetVec, targetTransform->getX() - t->getX(), targetTransform->getY() - t->getY());

					float angle = (myVel.x * targetVec.x + myVel.y*targetVec.y) / (Vector2DLength(&myVel) * Vector2DLength(&targetVec));
					float a = std::min(MAX_HOMING_ROTATION_SPEED * framerateController.getFrameTime(), acosf(angle));

					if (normal.x * targetVec.x + normal.y * targetVec.y < 0)
					{
						a = -a;
					}

					float curAngle = t->getRotation();
					Vector2DSet(&out, pBody->velX, pBody->velY);
					Vector2DNormalize(&out, &out);
					float scale = 1.f;
					if (g->getType() == GAME_OBJECT_TYPE::MISSILE)
					{
						scale = MISSILE_SPEED;
					}

					else if (g->getType() == GAME_OBJECT_TYPE::ALIEN)
					{
						scale = MISSILE_SPEED;
						scale /= 2.f;

					}

					Vector2DScale(&out, &out, scale);

					pBody->velX = out.x;
					pBody->velY = out.y;

				}
			}

		}



//Have all contacts
//Advnced physics applies here


//Commit changes back to Transform components

}