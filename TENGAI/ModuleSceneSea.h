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

	SDL_Texture * graphics1 = nullptr;
	SDL_Texture * graphics2 = nullptr;
	SDL_Texture * graphics3 = nullptr;
	SDL_Texture * graphics4 = nullptr;
	SDL_Rect waterfall1, waterfall2, waterfall3, waterfall4, waterfall5, waterfall6, waterfall7;
	SDL_Rect BG_far;
	SDL_Rect waves1, waves2, waves3, waves4, waves5;

	Mix_Music* SceneSea = nullptr;

};

#endif // __ModuleSceneSea_H__
