#ifndef __ModuleSceneForest_H__
#define __ModuleSceneForest_H__

#include "Module.h"

#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment(lib,"SDL_mixer/libx86/SDL2_mixer.lib")

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

	Mix_Music* SceneForest = nullptr;

};

#endif // __ModuleSceneForest_H__