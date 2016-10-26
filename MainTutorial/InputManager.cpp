#include "InputManager.h"
InputManager::InputManager()
{



	SDL_memset(previousState, 0, 512 * sizeof(Uint8));
	SDL_memset(currentState, 0, 512 * sizeof(Uint8));



}


InputManager::~InputManager()
{

}



void InputManager::Update(void)
{
	SDL_memcpy(previousState, currentState, 512 * sizeof(Uint8));
	int numKeys = 512;
	const Uint8* keyboardState = SDL_GetKeyboardState(&numKeys);
	//const Uint8* state = SDL_GetKeyboardState()
	if (numKeys > 512)
	{
		numKeys = 512;
	}

	
	SDL_memcpy(currentState, keyboardState, numKeys * sizeof(Uint8));



}



bool InputManager::isKeyReleased(unsigned int keyScanCode)
{
	if (keyScanCode >512)
	{
		return false;
		//keyScanCode = 512;
	}

	if (previousState[keyScanCode] == 1 && currentState[keyScanCode] == 0)
	{
		return true;
	}

	return false;
}


bool InputManager::isKeyTriggered(unsigned int keyScanCode)
{
	if (keyScanCode >512)
	{
		return false;
		//keyScanCode = 512;
	}

	if (previousState[keyScanCode] == 0 && currentState[keyScanCode] == 1)
	{
		return true;
	}

	return false;
}


bool InputManager::isKeyPressed(unsigned int keyScanCode)
{
	if (keyScanCode >512)
	{
		return false;
		//keyScanCode = 512;
	}

	if (currentState[keyScanCode])
	{
		return true;
	}

	return false;
}