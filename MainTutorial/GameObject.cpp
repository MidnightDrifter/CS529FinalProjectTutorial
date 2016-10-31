#include "GameObject.h"



GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}

void GameObject::Update()
{
	for (auto i = components.begin(); i!= components.end();i++)
	{
		i->Update();
	}
}
