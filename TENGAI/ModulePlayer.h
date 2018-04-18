#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment(lib,"SDL_mixer/libx86/SDL2_mixer.lib")

struct SDL_Texture;
struct Collider;

class ModulePlayer : public Module
{
public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

	void Die();
	void Touched();

	bool Touch_Animation = false;
	bool Shield_Animation = false;
	bool Die_Animation = false;
	void OnCollision(Collider* c1, Collider* c2);

public:

	SDL_Texture* graphics = nullptr;

	Animation* current_animation = nullptr;
	Animation idle;
	Animation touch;
	Animation backward;
	Animation run;
	Animation die;
	Animation shield;

	int Mlife = 3;

	Collider* player_collider;
	Collider* bullet_collider;

	iPoint position;
	iPoint screen_position;

	Mix_Chunk* MikosShot = nullptr;
	Mix_Chunk* MikoCollision = nullptr;


	bool alive = true;
	bool touched = false;
	int power_ups = 1;
};

#endif