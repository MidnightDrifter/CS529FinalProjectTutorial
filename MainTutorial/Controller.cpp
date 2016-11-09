#include "Controller.h"
#include "InputManager.h"
#include "GameObject.h"
#include "Body.h"
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
		static_cast<Body*>((this->owner->getComponent(COMPONENT_TYPE::BODY)))->velX-=(3.f);
	}

	if (InputMgr.isKeyPressed(SDL_SCANCODE_RIGHT))
	{
		static_cast<Body*>((this->owner->getComponent(COMPONENT_TYPE::BODY)))->velX += (3.f);
	}

	if (InputMgr.isKeyPressed(SDL_SCANCODE_DOWN))
	{
		static_cast<Body*>((this->owner->getComponent(COMPONENT_TYPE::BODY)))->velY -= (3.f);
	}

	if (InputMgr.isKeyPressed(SDL_SCANCODE_UP))
	{
		static_cast<Body*>((this->owner->getComponent(COMPONENT_TYPE::BODY)))->velY += (3.f);
	}
}
