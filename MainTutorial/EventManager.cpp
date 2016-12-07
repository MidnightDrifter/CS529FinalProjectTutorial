#include "EventManager.h"
#include "GameObjectManager.h"
#include "GameObject.h"

#include <list>


extern GameObjectManager& GameObjMgr;
EventManager::EventManager()
{
}


EventManager::~EventManager()
{
	for (Event* e : events)
	{
		delete e;
	}
	events.clear();
}

void EventManager::BroadcastEvent(Event* e)
{
	for (GameObject* g : GameObjMgr.objects)
	{

		g->HandleEvent(e);
	}
}

void EventManager::AddEvent(Event* e)
{
	if (e->timer <= 0.f)
	{
		BroadcastEvent(e);
		delete e;
	}
	else
	{
		events.push_back(e);
	}
}

void EventManager::Update(float frametime)
{
	std::list<Event*>::iterator it, itTemp;
	it = events.begin();

	while (it != events.end())
	{
		Event* pEvent = *it;
		pEvent->timer -= frametime;
		if (pEvent->timer <= 0.f)
		{
			BroadcastEvent(pEvent);
			delete pEvent;

			//Remove the popped event from the list
			itTemp = it;
			++itTemp;
			events.erase(it);
			it = itTemp;
		}
		
		else
		{
			it++;
		}
	}
}