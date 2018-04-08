#ifndef __ModuleSceneForest_H__
#define __ModuleSceneForest_H__

#include "Module.h"

struct SDL_Texture;

class ModuleSceneForest : public Module
{
public:
	ModuleSceneForest();
	~ModuleSceneForest();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture * graphics = nullptr;
	SDL_Rect BG_mid;
	SDL_Rect BG_far;
	SDL_Rect ground;

};

#endif // __ModuleSceneForest_H__