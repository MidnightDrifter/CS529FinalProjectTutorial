#pragma once
//#include <SDL.h>
#include <unordered_map>
#include <string>

struct SDL_Surface;

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	SDL_Surface * loadSurface(std::string fileName);
	SDL_Surface* loadSurface(const char* filename);

private:
	std::unordered_map<std::string, SDL_Surface *> mSurfaces;




};
