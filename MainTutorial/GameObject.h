#pragma once
#include <vector>
#include "Component.h"
class GameObject
{
public:
	GameObject();
	~GameObject();

	void Update();

private:
	std::vector<Component*> components;
};

