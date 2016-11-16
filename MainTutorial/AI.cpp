/*
#include "AI.h"
#include "EventManager.h"
#include "Transform.h"
#include "GameObject.h"
extern EventManager& EventMgr;

AI::AI() : Component(COMPONENT_TYPE::AI)
{
}


AI::~AI()
{
}


void AI::handleEvent(Event* e)
{

	if (EVENT_TYPE::PLAYERHIT == e->eType)
	{
		Transform* t = static_cast<Transform*>(owner->getComponent(COMPONENT_TYPE::TRANSFORM));
	
		if (NULL != t)
		{
			//Move the object to the right
			t->plusEqualX(50.f);
		}
	
	}

}
*/