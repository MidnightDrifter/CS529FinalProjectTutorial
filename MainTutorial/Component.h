#pragma once

enum COMPONENT_TYPE
{ 
	CONTROLLER,
	TRANSFORM,
	SPRITE,
	PHYSICS,
	
	NUM_COMPONENTS 

};


class Component
{
public:
	Component();
	virtual ~Component();
	virtual void Update();
	virtual void Serialize();


private:
		COMPONENT_TYPE type;
};

