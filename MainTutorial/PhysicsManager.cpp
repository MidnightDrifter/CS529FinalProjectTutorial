#include "PhysicsManager.h"
#include "CollisionManager.h"
#include "Transform.h"
extern GameObjectManager& GameObjMgr;
//extern FramerateController framerateController;
extern CollisionManager& CollisionMgr;
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
			
			if (NULL!=pBody)
			{
				Transform *pTransform = (Transform*)g->getComponent(COMPONENT_TYPE::TRANSFORM);
				//pTransform->Integrate(deltaTime *0.0
				pTransform->setX(pBody->currPosX);
				pTransform->setY(pBody->currPosY);
			}




		}



//Have all contacts
//Advnced physics applies here


//Commit changes back to Transform components

}