#include "FramerateController.h"


FramerateController::FramerateController(Uint32 m) : tickStart(0), tickEnd(0), frameTime(0)
{
	Uint32 a = m;
	if (m == 0)
	{
		a = UINT_MAX;
	}
	maxFramerate = a;
	//in ms so
	ticksPerFrame = 1000 / a;
	



}


void FramerateController::FrameStart()
{
	tickStart = SDL_GetTicks();
}


void FramerateController::FrameEnd()
{
	tickEnd = SDL_GetTicks();

	while (tickEnd - tickStart < ticksPerFrame)
	{
		tickEnd = SDL_GetTicks();

	}


	frameTime = tickEnd - tickStart;
}


Uint32 FramerateController::getFrameTime()
{
	return frameTime;
}
FramerateController::~FramerateController()
{
}
