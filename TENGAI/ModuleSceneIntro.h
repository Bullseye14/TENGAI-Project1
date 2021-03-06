#ifndef __ModuleSceneIntro_H__
#define __ModuleSceneIntro_H__

#include "Module.h"

#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment(lib,"SDL_mixer/libx86/SDL2_mixer.lib")

struct SDL_Texture;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro();
	~ModuleSceneIntro();

	bool Start();

	update_status Update();

	bool CleanUp();

public:
	SDL_Texture * background = nullptr;
	SDL_Texture * clouds = nullptr;

	Mix_Music* intro = nullptr;

	Mix_Chunk* IntroFX = nullptr;

};

#endif //__ModuleSceneIntro_H__