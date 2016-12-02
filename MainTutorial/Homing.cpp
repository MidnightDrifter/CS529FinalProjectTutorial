#include "Homing.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "Body.h"
#include "CollisionManager.h"

extern CollisionManager CollisionMgr;
extern GameObjectManager GameObjMgr;
//void Homing::Update()
//{
//	if (NULL == target)
//	{
//		if (this->owner->getType() == GAME_OBJECT_TYPE::PLAYER)
//		{
//			//Acquire a new target
//		}
//
//		else
//		{
//			//Destroy object--it will be a kamikaze enemy, and we want to reset them anyways(?)
//		}
//	}
//
//	Body* b = static_cast<Body*>(owner->getComponent(COMPONENT_TYPE::BODY));
//	if (b)
//	{
//		//Track target, report collision
//	}
//
//}

Homing::~Homing()
{
}
