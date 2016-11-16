#pragma once
#include "Component.h"
#include "EventManager.h"
class Event;

class PlayerHitEvent : public Event
{
public:
	PlayerHitEvent() : Event(EVENT_TYPE::PLAYERHIT) {}
	~PlayerHitEvent() {}
};


class Controller :
	public Component
{
public:
	Controller();
	~Controller();
	void Serialize(FILE** fpp) {}
	void Update();
	void handleEvent(Event* e);
	
};

