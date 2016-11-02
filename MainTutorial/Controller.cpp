#include "Controller.h"
#include "InputManager.h"
#include "GameObject.h"
#include "Transform.h"
extern InputManager InputMgr;

Controller::Controller() : Component(COMPONENT_TYPE::CONTROLLER)
{
	
}


Controller::~Controller()
{
}

void Controller::Update()
{
	//if left key pressed
	if (InputMgr.isKeyPressed(SDL_SCANCODE_LEFT))
	{
		static_cast<Transform*>((this->owner->getComponent(COMPONENT_TYPE::TRANSFORM)))->minusEqualX(3.f);
	}

	if (InputMgr.isKeyPressed(SDL_SCANCODE_RIGHT))
	{
		static_cast<Transform*>((this->owner->getComponent(COMPONENT_TYPE::TRANSFORM)))->plusEqualX(3.f);
	}

	if (InputMgr.isKeyPressed(SDL_SCANCODE_DOWN))
	{
		static_cast<Transform*>((this->owner->getComponent(COMPONENT_TYPE::TRANSFORM)))->minusEqualY(3.f);
	}

	if (InputMgr.isKeyPressed(SDL_SCANCODE_UP))
	{
		static_cast<Transform*>((this->owner->getComponent(COMPONENT_TYPE::TRANSFORM)))->plusEqualY(3.f);
	}
}
