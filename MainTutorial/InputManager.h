#pragma once
#include <SDL.h>
#include <memory>
class InputManager {



public:
	InputManager();
	~InputManager();
	bool isKeyTriggered(unsigned int keyScanCode);
	bool isKeyReleased(unsigned int keyScanCode);
	bool isKeyPressed(unsigned int keyScanCode);
	void Update();

private:
	Uint8 previousState[512];
	Uint8 currentState[512];
};
