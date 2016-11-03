#include "ResourceManager.h"
#include <SDL.h>


ResourceManager::ResourceManager() 
{
}

ResourceManager::~ResourceManager()
{
	for (auto i : mSurfaces)
	{
		SDL_FreeSurface((i.second));
	}

	mSurfaces.clear();
}



SDL_Surface * ResourceManager::loadSurface(const char* fileName)
{
	SDL_Surface *pSurface = mSurfaces[fileName];

	if (pSurface != NULL)
	{
		return pSurface;
	}

	pSurface = SDL_LoadBMP(fileName);

	if (pSurface != NULL)
	{
		mSurfaces[fileName]=pSurface;
	}

	return pSurface;
}



SDL_Surface * ResourceManager::loadSurface(std::string fileName)
{
	
	const char *name = fileName.c_str();
	return loadSurface(name);
}