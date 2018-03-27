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
	
	SDL_Texture* background_TENGAI = nullptr;
	SDL_Rect background_T;

	SDL_Texture* miko_text = nullptr;
	SDL_Rect miko;

	/*
	SDL_Texture* graphics = nullptr;
	SDL_Rect ground;
	SDL_Rect ship;
	Animation flag;
	Animation girl;
	Animation ryu;
	Animation twomen;
	Animation greenAN;
	Animation blueAN;
	Animation brownAN;
	Animation purpleAN;
	*/

};

#endif