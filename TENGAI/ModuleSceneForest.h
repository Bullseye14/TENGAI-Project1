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
	SDL_Rect TempleDoor;
	SDL_Rect ForestHouse1, ForestHouse2;
	SDL_Rect tree1, tree2, tree3, tree4, tree5, trees;
	SDL_Rect log1, log2;
	SDL_Rect floor1, floor2, floor3, floor4, floor5, floor6;
	SDL_Rect sky;
	SDL_Rect GreySquare, BlueSquare, BlackSquare;
	SDL_Rect mountain;

	Mix_Music* SceneForest = nullptr;

};

#endif // __ModuleSceneForest_H__