#pragma once
#include <vector>
class Component;

class GameObject
{
public:
	GameObject();
	~GameObject();

private:
	std::vector<Component*> components;
};

