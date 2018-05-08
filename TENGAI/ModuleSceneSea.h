#ifndef __ModuleSceneSea_H__
#define __ModuleSceneSea_H__

#include "Module.h"

#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment(lib,"SDL_mixer/libx86/SDL2_mixer.lib")

struct SDL_Texture;

class ModuleSceneSea : public Module
{
public:
	ModuleSceneSea();
	~ModuleSceneSea();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture * graphics = nullptr;

	Mix_Music* SceneSea = nullptr;

};

#endif // __ModuleSceneSea_H__
