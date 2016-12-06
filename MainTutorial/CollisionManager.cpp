#include "CollisionManager.h"
#include "Body.h"
#include "Math2D.h"
#include "Vector2D.h"


Shape::Shape(SHAPE_TYPE t) : shapeType(t), bodyOwner(NULL)
{

}




ShapeCircle::ShapeCircle() : Shape(SHAPE_TYPE::CIRCLE), radius(0.f)
{

}

ShapeCircle::~ShapeCircle() {}

bool ShapeCircle::TestPoint(float x, float y)
{
	Vector2D* point;
	point->x = x;
	point->y = y;

	Vector2D* c;
	c->x = this->bodyOwner->currPosX;
	c->y = this->bodyOwner->currPosY;



	return 1==StaticPointToStaticCircle(point,c,this->radius);
}


ShapeAABB::ShapeAABB() : Shape(SHAPE_TYPE::AABB), left(0.f), right(0.f), top(0.f), bot(0.f){}
ShapeAABB::~ShapeAABB() {}
bool ShapeAABB::TestPoint(float x, float y)
{
	Vector2D* point;
	point->x = x;
	point->y = y;
	float w = this->right - this->left;
	float h = this->top - this->bot;
	Vector2D* rect;
	rect->x = this->bodyOwner->currPosX;
	rect->y = this->bodyOwner->currPosY;

	return 1 == StaticPointToStaticRect(point, rect, w, h);
	
}



void CollisionManager::Reset(void)
{
	for (auto i : contacts)
	{
		delete i;
	}

	contacts.clear();
}

bool CheckCollisionCircleCircle(Shape* circle1, float posX1, float posY1, Shape* circle2, float posX2, float posY2, std::list<Contact*> &c, float shapeScale1X, float shapeScale1Y, float shapeScale2X, float shapeScale2Y)
{
	//Check for collision between shapes
	Vector2D c1, c2;
	Vector2DSet(&c1, posX1, posY1);
	Vector2DSet(&c2, posX2, posY2);
	ShapeCircle* circ1 = static_cast<ShapeCircle*>(circle1);
	ShapeCircle* circ2 = static_cast<ShapeCircle*>(circle2);

	//If collision, create contact
	if (1 == StaticCircleToStaticCircle(&c1, circ1->radius, &c2, circ2->radius)) //Collision check goes here
	{
		Contact*pc = new Contact();
		pc->bodiesColliding[0] = circle1->bodyOwner;
		pc->bodiesColliding[1] = circle2->bodyOwner;

		c.push_back(pc);
		return true;
	}
	return false;
}


bool CheckCollisionAABBAABB(Shape* AABB1, float posX1, float posY1, Shape* AABB2, float posX2, float posY2, std::list<Contact*> &c, float shapeScale1X, float shapeScale1Y, float shapeScale2X, float shapeScale2Y)
{
	//Check for collision between shapes, 
	Vector2D rect1, rect2;
	float w1, w2, h1, h2;

	Vector2DSet(&rect1, posX1, posY1);
	Vector2DSet(&rect2, posX2, posY2);

	ShapeAABB* r1 = static_cast<ShapeAABB*>(AABB1);
	ShapeAABB* r2 = static_cast<ShapeAABB*>(AABB2);


	//If collision, create contact
	if (1==StaticRectToStaticRect(&rect1, shapeScale1X*(r1->right - r1->left), shapeScale1Y*(r1->top - r1->bot),&rect2, shapeScale2X*(r2->right - r2->left), shapeScale2Y*(r2->top - r2->bot) )) //Collision check goes here 
	{
		Contact*pc = new Contact();
	pc->bodiesColliding[0] = AABB1->bodyOwner;
	pc->bodiesColliding[1] = AABB2->bodyOwner;

	c.push_back(pc);
	return true;
	}
	return false;
}



bool CheckCollisionCircleAABB(Shape* circle1, float posX1, float posY1, Shape* AABB2, float posX2, float posY2, std::list<Contact*> &c, float shapeScale1X, float shapeScale1Y, float shapeScale2X, float shapeScale2Y)
{
	//Check for collision between shapes
	ShapeCircle* ci = static_cast<ShapeCircle*>(circle1);
		ShapeAABB* r = static_cast<ShapeAABB*>(AABB2);

		Vector2D circ1, rect1;
		Vector2DSet(&circ1, posX1, posY1);
		Vector2DSet(&rect1, posX2, posY2);
	//If collision, create contact

	if (1==StaticCircleToStaticRectangle(&circ1, ci->radius, &rect1, shapeScale2X*(r->left - r->right), shapeScale2Y*(r->top - r->bot))) //Collision check goes here
	{
		Contact*pc = new Contact();
		pc->bodiesColliding[0] = circle1->bodyOwner;
		pc->bodiesColliding[1] = AABB2->bodyOwner;

		c.push_back(pc);
		return true;
	}
	return false;
}


bool CheckCollisionAABBCircle(Shape* AABB1, float posX1, float posY1, Shape* circle2, float posX2, float posY2, std::list<Contact*> &c, float shapeScale1X, float shapeScale1Y, float shapeScale2X, float shapeScale2Y)
{
	//Check for collision between shapes


	//If collision, create contact

	return CheckCollisionCircleAABB(circle2, posX2, posY2, AABB1, posX1, posY1, c, shapeScale1X, shapeScale1Y, shapeScale2X, shapeScale2Y);

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



bool CollisionManager::CheckCollisionGenerateContacts(Shape* shape1, float posX1, float posY1, Shape* shape2, float posX2, float posY2, float shapeScale1X, float shapeScale1Y, float shapeScale2X, float shapeScale2Y)
{
	return CollisionTable[(int)shape1->shapeType][(int)shape2->shapeType](shape1, posX1, posY1, shape2, posX2, posY1, contacts, shapeScale1X, shapeScale1Y, shapeScale2X, shapeScale2Y);
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


	contacts.clear();
}
