#pragma once

enum COMPONENT_TYPE
{ 
	
	NUM_COMPONENTS 

};


class Component
{
public:
	Component();
	virtual ~Component();

private:
		COMPONENT_TYPE type;
};

