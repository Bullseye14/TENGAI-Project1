#ifndef __ModuleSceneRanking_H__
#define __ModuleSceneRanking_H__

#include "Module.h"

#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment(lib,"SDL_mixer/libx86/SDL2_mixer.lib")

struct SDL_Texture;

class ModuleSceneRanking : public Module
{
public:
	ModuleSceneRanking();
	~ModuleSceneRanking();

	bool Start();

	update_status Update();

	bool CleanUp();

public:
	SDL_Texture * background_ranking = nullptr;
	SDL_Texture * stars = nullptr;
	int font = -1;


	Mix_Music* AudioRanking = nullptr;

};

#endif //__ModuleSceneRanking_H__
