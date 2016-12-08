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
extern GameObject* player;
extern CollisionManager& CollisionMgr;
#define MY_PI  3.14159265358979323846f 
const float rad = MY_PI/180.f;
Controller::Controller() : Component(COMPONENT_TYPE::CONTROLLER)
{
	
}


Controller::~Controller()
{
}

void Controller::Update()
{
	Transform* t = static_cast<Transform*>((this->owner->getComponent(COMPONENT_TYPE::TRANSFORM)));
	//float SHIP_ACCELERATION = 3000000.f;
	float SHIP_SPEED = 300000.f;
	float SHIP_ROTATION_SPEED = 75.f;// *rad;
	//if left key Triggered
	Body* b = static_cast<Body*>(owner->getComponent(COMPONENT_TYPE::BODY));

	/*


	if (t->rotation < 0)
	{
		t->rotation += 360;
	}

	else
	{
		while (t->rotation >= 360)
		{
			t->rotation -= 360;
		}
	}

	*/
	if (InputMgr.isKeyPressed(SDL_SCANCODE_LEFT))
	{
		t->rotation -= SHIP_ROTATION_SPEED;
		b->velX = -SHIP_SPEED;

	}

	if (InputMgr.isKeyPressed(SDL_SCANCODE_RIGHT))
	{
		t->rotation += SHIP_ROTATION_SPEED;
		b->velX = SHIP_SPEED;
	}

	int f = t->rotation;

	if (InputMgr.isKeyPressed(SDL_SCANCODE_DOWN))
	{
//		f %= f;

		//static_cast<Body*>((this->owner->getComponent(COMPONENT_TYPE::BODY)))->accelX -= (SHIP_ACCELERATION * cosf(f*rad));
		//static_cast<Body*>((this->owner->getComponent(COMPONENT_TYPE::BODY)))->accelY -= (SHIP_ACCELERATION * sinf(f*rad));

		b->velY = SHIP_SPEED;
	}

	if (InputMgr.isKeyPressed(SDL_SCANCODE_UP))
	{
	//	f %= f;

		//static_cast<Body*>((this->owner->getComponent(COMPONENT_TYPE::BODY)))->accelX += (SHIP_ACCELERATION * cosf(f *rad));
		//static_cast<Body*>((this->owner->getComponent(COMPONENT_TYPE::BODY)))->accelY += (SHIP_ACCELERATION * sinf(f*rad));
	
		b->velY = -SHIP_SPEED;
	}
	

	static_cast<Body*>((this->owner->getComponent(COMPONENT_TYPE::BODY)))->velY *= 0.9;
	static_cast<Body*>((this->owner->getComponent(COMPONENT_TYPE::BODY)))->velX *= 0.9;
	/*
	
	
		//if left key Triggered
	if (InputMgr.isKeyTriggered(SDL_SCANCODE_LEFT))
	{
		static_cast<Body*>((this->owner->getComponent(COMPONENT_TYPE::BODY)))->velX-=(3.f);
		//Rotate left

	}

	if (InputMgr.isKeyTriggered(SDL_SCANCODE_RIGHT))
	{
		static_cast<Body*>((this->owner->getComponent(COMPONENT_TYPE::BODY)))->velX += (3.f);
		//Rotate right
	}

	if (InputMgr.isKeyTriggered(SDL_SCANCODE_DOWN))
	{
		static_cast<Body*>((this->owner->getComponent(COMPONENT_TYPE::BODY)))->velY -= (3.f);
		//Backward accel
	}

	if (InputMgr.isKeyTriggered(SDL_SCANCODE_UP))
	{
		static_cast<Body*>((this->owner->getComponent(COMPONENT_TYPE::BODY)))->velY += (3.f);
		//Forward accel
	}
	*/
	if(InputMgr.isKeyTriggered(SDL_SCANCODE_SPACE))
	{
 		GameObject* bullet = GameObjMgr.spawnObject(GAME_OBJECT_TYPE::BULLET);
		Body* b = static_cast<Body*>(bullet->getComponent(COMPONENT_TYPE::BODY));
		Transform* t = static_cast<Transform*>(bullet->getComponent(COMPONENT_TYPE::TRANSFORM));
		
		//Transform* t = static_cast<Transform*>(bullet->getComponent(COMPONENT_TYPE::TRANSFORM));
		
		b->currPosX = (static_cast<Body*>((this->owner->getComponent(COMPONENT_TYPE::BODY)))->currPosX);
		b->currPosY = (static_cast<Body*>((this->owner->getComponent(COMPONENT_TYPE::BODY)))->currPosY);
		t->setX(static_cast<Transform*>((this->owner->getComponent(COMPONENT_TYPE::TRANSFORM)))->getX());
		t->setY(static_cast<Transform*>((this->owner->getComponent(COMPONENT_TYPE::TRANSFORM)))->getY());


		float BULLET_SPEED = 300555.f;
		float bulletRot = (static_cast<Transform*>(this->owner->getComponent(COMPONENT_TYPE::TRANSFORM))->getRotation());
		//t->setRotation(bulletRot);

		b->velX = BULLET_SPEED * cosf(bulletRot*rad);
		b->velY = BULLET_SPEED * sinf(bulletRot*rad);
		
		//b->velX = 1.f;   //Add rotation calculations here, scale by BULLET_SPEED
		//b->velY = 1.f;



		 bullet = GameObjMgr.spawnObject(GAME_OBJECT_TYPE::BULLET);
		 b = static_cast<Body*>(bullet->getComponent(COMPONENT_TYPE::BODY));
		 t = static_cast<Transform*>(bullet->getComponent(COMPONENT_TYPE::TRANSFORM));

		//Transform* t = static_cast<Transform*>(bullet->getComponent(COMPONENT_TYPE::TRANSFORM));

		b->currPosX = (static_cast<Body*>((this->owner->getComponent(COMPONENT_TYPE::BODY)))->currPosX);
		b->currPosY = (static_cast<Body*>((this->owner->getComponent(COMPONENT_TYPE::BODY)))->currPosY);
		t->setX(static_cast<Transform*>((this->owner->getComponent(COMPONENT_TYPE::TRANSFORM)))->getX());
		t->setY(static_cast<Transform*>((this->owner->getComponent(COMPONENT_TYPE::TRANSFORM)))->getY());


		
		 bulletRot = (static_cast<Transform*>(this->owner->getComponent(COMPONENT_TYPE::TRANSFORM))->getRotation());
		//t->setRotation(bulletRot);

		b->velX = -BULLET_SPEED * cosf(bulletRot*rad);
		b->velY = BULLET_SPEED * sinf(bulletRot*rad);

		 bullet = GameObjMgr.spawnObject(GAME_OBJECT_TYPE::BULLET);
		b = static_cast<Body*>(bullet->getComponent(COMPONENT_TYPE::BODY));
		 t = static_cast<Transform*>(bullet->getComponent(COMPONENT_TYPE::TRANSFORM));

		//Transform* t = static_cast<Transform*>(bullet->getComponent(COMPONENT_TYPE::TRANSFORM));

		b->currPosX = (static_cast<Body*>((this->owner->getComponent(COMPONENT_TYPE::BODY)))->currPosX);
		b->currPosY = (static_cast<Body*>((this->owner->getComponent(COMPONENT_TYPE::BODY)))->currPosY);
		t->setX(static_cast<Transform*>((this->owner->getComponent(COMPONENT_TYPE::TRANSFORM)))->getX());
		t->setY(static_cast<Transform*>((this->owner->getComponent(COMPONENT_TYPE::TRANSFORM)))->getY());


		
		 bulletRot = (static_cast<Transform*>(this->owner->getComponent(COMPONENT_TYPE::TRANSFORM))->getRotation());
		//t->setRotation(bulletRot);

		b->velX = BULLET_SPEED * cosf(bulletRot*rad);
		b->velY = -BULLET_SPEED * sinf(bulletRot*rad);

		 		 bullet = GameObjMgr.spawnObject(GAME_OBJECT_TYPE::BULLET);
		 b = static_cast<Body*>(bullet->getComponent(COMPONENT_TYPE::BODY));
		 t = static_cast<Transform*>(bullet->getComponent(COMPONENT_TYPE::TRANSFORM));
		
		//Transform* t = static_cast<Transform*>(bullet->getComponent(COMPONENT_TYPE::TRANSFORM));
		
		b->currPosX = (static_cast<Body*>((this->owner->getComponent(COMPONENT_TYPE::BODY)))->currPosX);
		b->currPosY = (static_cast<Body*>((this->owner->getComponent(COMPONENT_TYPE::BODY)))->currPosY);
		t->setX(static_cast<Transform*>((this->owner->getComponent(COMPONENT_TYPE::TRANSFORM)))->getX());
		t->setY(static_cast<Transform*>((this->owner->getComponent(COMPONENT_TYPE::TRANSFORM)))->getY());


		
		 bulletRot = (static_cast<Transform*>(this->owner->getComponent(COMPONENT_TYPE::TRANSFORM))->getRotation());
		//t->setRotation(bulletRot);

		b->velX = -BULLET_SPEED * cosf(bulletRot*rad);
		b->velY = -BULLET_SPEED * sinf(bulletRot*rad);
	}

	if (InputMgr.isKeyTriggered(SDL_SCANCODE_M))
	{
		GameObject* missile = GameObjMgr.spawnObject(GAME_OBJECT_TYPE::MISSILE);
			Body* b = static_cast<Body*>(missile->getComponent(COMPONENT_TYPE::BODY));
		Transform* t = static_cast<Transform*>(missile->getComponent(COMPONENT_TYPE::TRANSFORM));

		//Transform* t = static_cast<Transform*>(bullet->getComponent(COMPONENT_TYPE::TRANSFORM));


		b->currPosX = (static_cast<Body*>((this->owner->getComponent(COMPONENT_TYPE::BODY)))->currPosX);
		b->currPosY = (static_cast<Body*>((this->owner->getComponent(COMPONENT_TYPE::BODY)))->currPosY);
		
		t->setX(static_cast<Transform*>((this->owner->getComponent(COMPONENT_TYPE::TRANSFORM)))->getX());
		t->setY(static_cast<Transform*>((this->owner->getComponent(COMPONENT_TYPE::TRANSFORM)))->getY());


	}
	
	






}


void Controller::handleEvent(Event* e)
{
	if (e->eType == EVENT_TYPE::COLLISION)
	{
		CollisionEvent* cEvent = static_cast<CollisionEvent*>(e);

		Body* b = static_cast<Body*>(owner->getComponent(COMPONENT_TYPE::BODY));

		GameObject* otherCollider = NULL;

		if ( this->owner == cEvent->pObject1)
		{
			otherCollider = cEvent->pObject2;
		}

		else
		{
			otherCollider = cEvent->pObject1;
		}


		if (NULL != b && otherCollider != NULL && (otherCollider->getType() == GAME_OBJECT_TYPE::ALIEN || otherCollider->getType() == GAME_OBJECT_TYPE::ASTEROID || otherCollider->getType() == GAME_OBJECT_TYPE::SQUARE_MOVER))
		{
			//If something with a controller component collides with something, reset its position
		//	b->currPosX = 0;
		//	b->currPosY = 0;

			//Reset the controller object--this object--destroy the enemy object
		//	delete otherCollider;  //Destroy it through the game object manager instead??
			
		//	b->currPosX = 0.5f;  //Some starting position
		//	b->currPosY = 0.5f; 

			//Don't need player hit event, collision works just fine
			CollisionMgr.Reset();
			GameObjMgr.objects.clear();
		
			GameObjMgr.LoadLevel("TextFiles//Level.txt");
			for (int i = 0; i < GameObjMgr.objects.size(); i++)
			{
				if (GameObjMgr.objects[i]->getType() == GAME_OBJECT_TYPE::PLAYER)
				{
					player = GameObjMgr.objects[i];
					i = GameObjMgr.objects.size();
				}
			}

			
		
		}
		/*
		//Timer of 2s
		PlayerHitEvent* phe = new PlayerHitEvent();
		phe->timer = 2;
		EventMgr.AddEvent(phe);
	*/
	
	}
}
