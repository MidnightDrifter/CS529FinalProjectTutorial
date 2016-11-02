#include "Component.h"


Component::Component(COMPONENT_TYPE c) : owner(), type(c)
{
}


Component::~Component()
{
	//delete owner;
}

void Component::setOwner(GameObject* own)
{
	owner = own;
}