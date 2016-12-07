#include "SquareMover.h"
#include "Body.h"
#include "FramerateController.h"
extern FramerateController& framerateController;




SquareMover::~SquareMover()
{
}

void SquareMover::Serialize(FILE** fpp)
{
	fscanf(*fpp, "%f %f\n", &timer, &speed);

}

void SquareMover::Update()
{
	
	counter += framerateController.getFrameTime();

	if (counter >= timer)
	{
		Body* b = static_cast<Body*>(owner->getComponent(COMPONENT_TYPE::BODY));
		if (fourHolder == 0)
		{
			b->velX = speed;
			b->velY = 0;
			fourHolder++;
		}

		else if (fourHolder == 1)
		{
			fourHolder++;
			b->velX = 0;
			b->velY = speed;
		}

		else if (fourHolder == 2)
		{
			fourHolder++;
			b->velX = -speed;
			b->velY = 0;
		}

		else if (fourHolder == 3)
		{
			fourHolder = 0;
			b->velX = 0;
			b->velY = -speed;
		}
		counter = 0;
	}

}