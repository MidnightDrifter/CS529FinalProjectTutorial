#include "Controller.h"
#include "InputManager.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "ResourceManager.h"
#include "Body.h"
#include "EventManager.h"
#include "PhysicsManager.h"
extern InputManager& InputMgr;
extern GameObjectManager& GameObjMgr;
extern ResourceManager& ResourceMgr;
extern EventManager& EventMgr;

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
		static_cast<Body*>((this->owner->getComponent(COMPONENT_TYPE::BODY)))->velX-=(300.f);
	}

	if (InputMgr.isKeyPressed(SDL_SCANCODE_RIGHT))
	{
		static_cast<Body*>((this->owner->getComponent(COMPONENT_TYPE::BODY)))->velX += (300.f);
	}

	if (InputMgr.isKeyPressed(SDL_SCANCODE_DOWN))
	{
		static_cast<Body*>((this->owner->getComponent(COMPONENT_TYPE::BODY)))->velY += (300.f);
	}

	if (InputMgr.isKeyPressed(SDL_SCANCODE_UP))
	{
		static_cast<Body*>((this->owner->getComponent(COMPONENT_TYPE::BODY)))->velY -= (300.f);
	}
	
	/*
	
	
		//if left key pressed
	if (InputMgr.isKeyPressed(SDL_SCANCODE_LEFT))
	{
		static_cast<Body*>((this->owner->getComponent(COMPONENT_TYPE::BODY)))->velX-=(3.f);
		//Rotate left

	}

	if (InputMgr.isKeyPressed(SDL_SCANCODE_RIGHT))
	{
		static_cast<Body*>((this->owner->getComponent(COMPONENT_TYPE::BODY)))->velX += (3.f);
		//Rotate right
	}

	if (InputMgr.isKeyPressed(SDL_SCANCODE_DOWN))
	{
		static_cast<Body*>((this->owner->getComponent(COMPONENT_TYPE::BODY)))->velY -= (3.f);
		//Backward accel
	}

	if (InputMgr.isKeyPressed(SDL_SCANCODE_UP))
	{
		static_cast<Body*>((this->owner->getComponent(COMPONENT_TYPE::BODY)))->velY += (3.f);
		//Forward accel
	}
	*/
	if(InputMgr.isKeyPressed(SDL_SCANCODE_SPACE))
	{
		GameObject* bullet = GameObjMgr.spawnObject(GAME_OBJECT_TYPE::BULLET);

		Body* b = static_cast<Body*>(bullet->getComponent(COMPONENT_TYPE::BODY));
		//Transform* t = static_cast<Transform*>(bullet->getComponent(COMPONENT_TYPE::TRANSFORM));
		
		//b->currPosX = (static_cast<Body*>((this->owner->getComponent(COMPONENT_TYPE::BODY)))->currPosX);
		//b->currPosY = (static_cast<Body*>((this->owner->getComponent(COMPONENT_TYPE::BODY)))->currPosY);
		//b->velX = 1.f;   //Add rotation calculations here, scale by BULLET_SPEED
		//b->velY = 1.f;

	}
	
	






}


void Controller::handleEvent(Event* e)
{
	if (e->eType == EVENT_TYPE::COLLISION)
	{
		CollisionEvent* cEvent = static_cast<CollisionEvent*>(e);
		Body* b = static_cast<Body*>(owner->getComponent(COMPONENT_TYPE::BODY));

		if (NULL != b)
		{
			//If something with a controller component collides with something, reset its position
			b->currPosX = 0;
			b->currPosY = 0;
		}

		//Timer of 2s
		PlayerHitEvent* phe = new PlayerHitEvent();
		phe->timer = 2;
		EventMgr.AddEvent(phe);
	}
}
