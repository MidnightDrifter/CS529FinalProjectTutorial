#include "CollisionManager.h"
#include "Body.h"


Shape::Shape(SHAPE_TYPE t) : shapeType(t), bodyOwner(NULL)
{

}




ShapeCircle::ShapeCircle() : Shape(SHAPE_TYPE::CIRCLE), radius(0.f)
{

}

ShapeCircle::~ShapeCircle() {}

bool ShapeCircle::TestPoint(float x, float y)
{
	return true;
}


ShapeAABB::ShapeAABB() : Shape(SHAPE_TYPE::AABB), left(0.f), right(0.f), top(0.f), bot(0.f){}
ShapeAABB::~ShapeAABB() {}
bool ShapeAABB::TestPoint(float x, float y)
{
	return true;
}



void CollisionManager::Reset(void)
{
	for (auto i : contacts)
	{
		delete i;
	}

	contacts.clear();
}

bool CheckCollisionCircleCircle(Shape* circle1, float posX1, float posY1, Shape* circle2, float posX2, float posY2, std::list<Contact*> &c)
{
	//Check for collision between shapes
	

	//If collision, create contact
	if (true) //Collision check goes here
	{
		Contact*pc = new Contact();
		pc->bodiesColliding[0] = circle1->bodyOwner;
		pc->bodiesColliding[1] = circle2->bodyOwner;

		c.push_back(pc);
		return true;
	}
	return false;
}


bool CheckCollisionAABBAABB(Shape* AABB1, float posX1, float posY1, Shape* AABB2, float posX2, float posY2, std::list<Contact*> &c)
{
	//Check for collision between shapes


	//If collision, create contact
	if (true) //Collision check goes here 
	{
		Contact*pc = new Contact();
	pc->bodiesColliding[0] = AABB1->bodyOwner;
	pc->bodiesColliding[1] = AABB2->bodyOwner;

	c.push_back(pc);
	return true;
	}
	return false;
}



bool CheckCollisionCircleAABB(Shape* circle1, float posX1, float posY1, Shape* AABB2, float posX2, float posY2, std::list<Contact*> &c)
{
	//Check for collision between shapes


	//If collision, create contact

	if (true) //Collision check goes here
	{
		Contact*pc = new Contact();
		pc->bodiesColliding[0] = circle1->bodyOwner;
		pc->bodiesColliding[1] = AABB2->bodyOwner;

		c.push_back(pc);
		return true;
	}
	return false;
}


bool CheckCollisionAABBCircle(Shape* AABB1, float posX1, float posY1, Shape* circle2, float posX2, float posY2, std::list<Contact*> &c)
{
	//Check for collision between shapes


	//If collision, create contact

	return CheckCollisionCircleAABB(circle2, posX2, posY2, AABB1, posX1, posY1, c);

}

//FUNCTION POINTERSSSSS
/*
				CIRCLE    AABB
			----------------------|
	CIRCLE	|			|		  |
			|			|		  |
			|-----------|---------|			
			|			|		  |
	AABB	|			|		  |



*/



bool CollisionManager::CheckCollisionGenerateContacts(Shape* shape1, float posX1, float posY1, Shape* shape2, float posX2, float posY2)
{
	return CollisionTable[(int)shape1->shapeType][(int)shape2->shapeType](shape1, posX1, posY1, shape2, posX2, posY1, contacts);
}



CollisionManager::CollisionManager() : contacts()
{
	CollisionTable[(int)Shape::SHAPE_TYPE::CIRCLE][(int)Shape::SHAPE_TYPE::CIRCLE] = CheckCollisionCircleCircle;
	CollisionTable[(int)Shape::SHAPE_TYPE::CIRCLE][(int)Shape::SHAPE_TYPE::AABB] = CheckCollisionCircleAABB;
	CollisionTable[(int)Shape::SHAPE_TYPE::AABB][(int)Shape::SHAPE_TYPE::CIRCLE] = CheckCollisionAABBCircle;
	CollisionTable[(int)Shape::SHAPE_TYPE::AABB][(int)Shape::SHAPE_TYPE::AABB] = CheckCollisionAABBAABB;


}


CollisionManager::~CollisionManager()
{
	for (auto i : contacts)
	{
		delete i;
	}

	contacts.clear();
}
