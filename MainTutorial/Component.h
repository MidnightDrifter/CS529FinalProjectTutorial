#pragma once
#include <stdio.h>
class GameObject;
class Event;
enum class COMPONENT_TYPE
{ 
	CONTROLLER,
	TRANSFORM,
	SPRITE,
	HOMING,
	BODY,
	SQUARE_MOVER
	
	


};


class Component
{
public:
	Component(COMPONENT_TYPE c);
	virtual ~Component();
	virtual void Update() =0;
	virtual void Serialize(FILE** fpp)=0;
	void setOwner(GameObject* o);
	COMPONENT_TYPE getType() const { return type; }
	void virtual handleEvent(Event* e) {}



		COMPONENT_TYPE type;
		GameObject* owner;
};

