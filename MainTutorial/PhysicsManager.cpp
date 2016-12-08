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
#define MISSILE_SPEED 15000.f;
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
		//	Transform* t1 = static_cast<Transform*>(GameObjMgr.objects.at(i)->getComponent(COMPONENT_TYPE::TRANSFORM));
			SpriteBasic* s1 = static_cast<SpriteBasic*>(GameObjMgr.objects.at(i)->getComponent(COMPONENT_TYPE::SPRITE));
			if (NULL != body1  && NULL != s1)
			{
				for (int j = i + 1; j < numObjects; j++)
				{
					Body* body2 = (Body*)GameObjMgr.objects.at(j)->getComponent(COMPONENT_TYPE::BODY);
					//Transform* t2 = static_cast<Transform*>(GameObjMgr.objects.at(j)->getComponent(COMPONENT_TYPE::TRANSFORM));
					SpriteBasic* s2 = static_cast<SpriteBasic*>(GameObjMgr.objects.at(j)->getComponent(COMPONENT_TYPE::SPRITE));
					if (NULL != body2 && body2 != body1 && NULL != s1 && NULL != s2)
					{
						int x1, y1, x2, y2;
						x1 = body1->currPosX;// -(s1->width / 2);
						y1 = body1->currPosY;// -(s1->height / 2);
						x2 = body2->currPosX;// -(s2->width / 2);
						y2 = body2->currPosY;// -(s2->height / 2);

						//CollisionMgr.CheckCollisionGenerateContacts(body1->shape, body1->currPosX, body1->currPosY, body2->shape, body2->currPosX, body2->currPosY, s1->width, s1->height, s2->width, s2->height);// t1->getXScale(), t1->getYScale(), t2->getXScale(), t2->getYScale());//
						CollisionMgr.CheckCollisionGenerateContacts(body1->shape, x1, y1, body2->shape, x2, y2, s1->width, s1->height, s2->width, s2->height);// t1->getXScale(), t1->getYScale(), t2->getXScale(), t2->getYScale());//

					
					}
				}

			}
		}

		for (auto a : CollisionMgr.contacts)
		{
			CollisionEvent c;
			c.pObject1 = a->bodiesColliding[0]->owner;
			c.pObject2 = a->bodiesColliding[1]->owner;
			if (c.pObject1 != NULL)
			{
				c.pObject1->HandleEvent(&c);
			}
			if (c.pObject2 != NULL)
			{
				c.pObject2->HandleEvent(&c);

			}

			if (c.pObject1 != NULL && c.pObject2 != NULL)
			{
				GameObject* p = NULL;
				GameObject* al = NULL;
				if (c.pObject1->getType() == GAME_OBJECT_TYPE::PLAYER)
				{
					p = c.pObject1;
				}

				 if (c.pObject2->getType() == GAME_OBJECT_TYPE::PLAYER)
				{
					p = c.pObject2;
				}

				 if (c.pObject1->getType() == GAME_OBJECT_TYPE::ALIEN || c.pObject1->getType() == GAME_OBJECT_TYPE::ASTEROID || c.pObject1->getType() == GAME_OBJECT_TYPE::SQUARE_MOVER)
				 {
					 al = c.pObject1;
				}
				 if (c.pObject2->getType() == GAME_OBJECT_TYPE::ALIEN || c.pObject2->getType() == GAME_OBJECT_TYPE::ASTEROID || c.pObject2->getType() == GAME_OBJECT_TYPE::SQUARE_MOVER)
				 {
					 al = c.pObject2;
				 }

				 if (p != NULL && a != NULL)
				 {
					 break;
				 }
			}
		}


		//Commit changes from physics -> transform	
		for (GameObject* g : GameObjMgr.objects)
		{
			Body *pBody = static_cast<Body*>(g->getComponent(COMPONENT_TYPE::BODY));
			Homing* h = static_cast<Homing*>(g->getComponent(COMPONENT_TYPE::HOMING));
			
			if (NULL != pBody && h != NULL)
			{
				Transform *pTransform = static_cast<Transform*>(g->getComponent(COMPONENT_TYPE::TRANSFORM));
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

					Body* targetBody = static_cast<Body*>(h->target->getComponent(COMPONENT_TYPE::BODY));

					Vector2D directionToTarget;
					Vector2DSet(&directionToTarget, targetBody->currPosX - pBody->currPosX, targetBody->currPosY - pBody->currPosY);
					Vector2DNormalize(&directionToTarget, &directionToTarget);





					
					
					/*
					Vector2D myVel, normal, targetVec, out;
					Vector2DSet(&myVel, pBody->velX, pBody->velY);
					Vector2DSet(&normal, myVel.y * -1, myVel.x);
					Vector2DSet(&targetVec, targetTransform->getX() - t->getX(), targetTransform->getY() - t->getY());

					float myLen = Vector2DLength(&myVel);
					float targetLen = Vector2DLength(&targetVec);
					float angle;
					if (myLen == 0 || targetLen == 0)
					{
						angle = 0.f;
					}
					else {
						angle = (myVel.x * targetVec.x + myVel.y*targetVec.y) / (Vector2DLength(&myVel) * Vector2DLength(&targetVec));
					}
						float a = std::min(MAX_HOMING_ROTATION_SPEED * framerateController.getFrameTime(), acosf(angle));

					if (normal.x * targetVec.x + normal.y * targetVec.y < 0)
					{
						a = -a;
					}

					float curAngle = t->getRotation();
					Vector2DSet(&out, pBody->velX, pBody->velY);
					Vector2DNormalize(&out, &out);
					*/
					float scale = 1.f;
					if (g->getType() == GAME_OBJECT_TYPE::MISSILE)
					{
						scale = MISSILE_SPEED;
					}

					else if (g->getType() == GAME_OBJECT_TYPE::ALIEN)
					{
						scale = MISSILE_SPEED;
						scale /= 2;
						//scale /= 4000.f;
						//scale = 0;

					}

					Vector2DScale(&directionToTarget, &directionToTarget, scale);

					pBody->velX = directionToTarget.x;
					pBody->velY = directionToTarget.y;
					
				}
				pBody = NULL;
				h = NULL;
			}

		}



//Have all contacts
//Advnced physics applies here


//Commit changes back to Transform components

}