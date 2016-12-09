#pragma once
#include <list>
#include "Math2D.h"
#include "Vector2D.h"

class Body;

class Shape
{
public:

	enum class SHAPE_TYPE
	{
		CIRCLE,
		AABB,



		NUM
	};

	Shape(SHAPE_TYPE t);
	virtual ~Shape() {}

	virtual bool TestPoint(float x, float y) = 0;
	



public:

	Body* bodyOwner;
	SHAPE_TYPE shapeType;


};




class ShapeCircle : public Shape
{
public:
	ShapeCircle();
	~ShapeCircle();

	virtual bool TestPoint(float x, float y);



	float radius;
	//Get position of center & shape from Body component
};



class ShapeAABB : public Shape
{
public:
	ShapeAABB();
	ShapeAABB(float l, float r, float t, float b) : Shape(SHAPE_TYPE::AABB), top(t), bot(b), left(l), right(r) {}
	~ShapeAABB();

	virtual bool TestPoint(float x, float y);

	float left, right, top, bot;
};




class Contact
{
public:
	Contact() { bodiesColliding[0] = NULL;
	bodiesColliding[1] = NULL; }
	~Contact() {}


	Body* bodiesColliding[2];


};





class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();
	void Reset(void);
	bool CheckCollisionGenerateContacts(Shape* shape1, float posX1, float posY1, Shape* shape2, float posX2, float posY2, float shapeScale1X, float shapeScale1Y, float shapeScale2X, float shapeScale2Y);
	std::list<Contact*> contacts;


	bool(* CollisionTable[(int)Shape::SHAPE_TYPE::NUM][(int)Shape::SHAPE_TYPE::NUM])(Shape* shape1, float posX1, float posY1, Shape* shape2, float posX2, float posY2, std::list<Contact*> &c, float shapeScale1X, float shapeScale1Y, float shapeScale2X, float shapeScale2Y);



private:


};

