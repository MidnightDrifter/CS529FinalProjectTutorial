#pragma once
#include "Component.h"
class SquareMover :
	public Component
{
public:
	SquareMover();
	~SquareMover();

	SquareMover() : timer(0), speed(0), counter(0), fourHolder(0), Component(COMPONENT_TYPE::SQUARE_MOVER) {}
	SquareMover(float f, float g) : timer(f), speed(g), counter(0), fourHolder(0), Component(COMPONENT_TYPE::SQUARE_MOVER) {}
	void Serialize(FILE** fpp);
	void handleEvent(Event* e) {}
	void Update();

	//float timer, speed;

private:
	float counter, timer, speed, fourHolder;
};

