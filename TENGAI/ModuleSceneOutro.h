#ifndef __ModuleSceneOutro_H__
#define __ModuleSceneOutro_H__

#include "Module.h"

#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment(lib,"SDL_mixer/libx86/SDL2_mixer.lib")

struct SDL_Texture;

class ModuleSceneOutro : public Module
{
public:
	ModuleSceneOutro();
	~ModuleSceneOutro();

	bool Start();

	update_status Update();

	bool CleanUp();

public:
	SDL_Texture * background_outro = nullptr;
	SDL_Texture * stars = nullptr;

	Mix_Music* AudioOutro = nullptr;

};

#endif //__ModuleSceneOutro_H__
