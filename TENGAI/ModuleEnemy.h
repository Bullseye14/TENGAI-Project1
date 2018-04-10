#ifndef __ModuleEnemy_H__
#define __ModuleEnemy_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment(lib,"SDL_mixer/libx86/SDL2_mixer.lib")

struct SDL_Texture;
struct Collider;

class ModuleEnemy :public Module
{
public:
	ModuleEnemy();
	~ModuleEnemy();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

public:

	SDL_Texture * enemy1 = nullptr;
	Animation* current_animation = nullptr;
	Animation enemyAnim;
	iPoint enemy_pos;
	Collider* enemy_collider;

	uint offsetCamera;
};

#endif