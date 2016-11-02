#include "GameObject.h"
#include "Component.h"


GameObject::GameObject() : components()
{
}


GameObject::~GameObject()
{
	for (auto i = components.begin(); i != components.end(); i++)
	{
		delete(*i);
	}
}

Component* GameObject::getComponent(COMPONENT_TYPE c)
{
	Component* out = NULL;
	for (std::vector<Component*>::iterator i = components.begin(); i != components.end(); i++)
	{
		if((*i)->getType() == c)
		{
			out = (*i);
			i = this->components.end();
		}
	}
	return out;
}

void GameObject::Update()
{
	for (auto i = components.begin(); i!= components.end();i++)
	{
		(*i)->Update();
	}
}

void GameObject::addComponent(Component* c)
{
	components.push_back(c);
}


