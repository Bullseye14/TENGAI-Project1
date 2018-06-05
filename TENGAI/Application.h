#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 17

class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleRender;
class ModuleParticles;
class ModuleSceneForest;
class ModuleSceneSea;
class ModuleMiko;
class ModuleFadeToBlack;
class Module;
class ModuleSceneIntro;
class ModuleAudio;
class ModuleSceneOutro;
class ModuleCollision;
class ModuleEnemies;
class ModuleSho;
class ModuleSceneRanking;
class ModuleFonts;


class Application
{
public:

	Module* modules[NUM_MODULES];
	ModuleWindow* window;
	ModuleRender* render;
	ModuleInput* input;
	ModuleTextures* textures;
	ModuleSceneForest* scene_forest;
	ModuleSceneSea* scene_sea;
	ModuleMiko* miko;
	ModuleFadeToBlack* fade;
	ModuleParticles* particles;
	ModuleSceneIntro* scene_intro;
	ModuleAudio* audio;
	ModuleSceneOutro* scene_outro;
	ModuleCollision* collision;
	ModuleEnemies* enemies;
	ModuleSho* sho;
	ModuleSceneRanking* scene_ranking;
	ModuleFonts* fonts;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__