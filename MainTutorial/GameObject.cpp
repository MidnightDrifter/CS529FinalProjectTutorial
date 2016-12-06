#include "GameObject.h"
#include "Component.h"



GameObject::GameObject() : components(), type(GAME_OBJECT_TYPE::NULLTYPE)
{
}


GameObject::GameObject(GAME_OBJECT_TYPE t) : components(), type(t) {}


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
			break;
		}
	}
	return out;
}

void GameObject::Update()
{
	for (int i=0;i<components.size();i++)
	{
		components.at(i)->Update();
	}
}

void GameObject::addComponent(Component* c)
{
	c->setOwner(this);
	components.push_back(c);
}

void GameObject::HandleEvent(Event* e)
{
	if (NULL != this )
	{
		int size = components.size();
		for (int i = 0; i < size; i++)
		{
			if (components[i] != NULL)
			{
				components[i]->handleEvent(e);
			}
			size = components.size();

		}
	}

}
