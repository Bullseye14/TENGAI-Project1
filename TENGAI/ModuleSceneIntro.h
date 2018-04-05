#ifndef __ModuleSceneIntro_H__
#define __ModuleSceneIntro_H__

#include "Module.h"

struct SDL_Texture;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro();
	~ModuleSceneIntro();

	bool Init();

	update_status Update();

	bool CleanUp();

public:
	SDL_Texture * background = nullptr;
	SDL_Texture * stars = nullptr;

};

#endif //__ModuleSceneIntro_H__