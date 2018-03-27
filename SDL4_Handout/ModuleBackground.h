#ifndef __ModuleBackground_H__
#define __ModuleBackground_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleBackground : public Module
{
public:
	ModuleBackground();
	~ModuleBackground();

	bool Start();
	update_status Update();

public:
	
	SDL_Texture* BG_forest_texture = nullptr;
	SDL_Rect BG_mid;
	SDL_Rect BG_far;
	SDL_Rect ground;
};

#endif