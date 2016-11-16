#pragma once
#include <list>
enum class EVENT_TYPE {
	COLLISION,
	PLAYERHIT,
	
	
	NUM
};

class Event {
public:
	Event(EVENT_TYPE t) : eType(t), timer(0.f){}
	Event(EVENT_TYPE t, float ti) : eType(t), timer(ti) {}

	virtual ~Event() {}

	EVENT_TYPE eType;
	float timer;
};

class EventManager
{
public:
	EventManager();
	~EventManager();
	void BroadcastEvent(Event* e);
	void AddEvent(Event* e);
	void Update(float frametime);

	std::list<Event*> events;
};

