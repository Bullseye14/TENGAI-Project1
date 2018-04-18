#ifndef __ModuleJunis_H__
#define __ModuleJunis_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment(lib,"SDL_mixer/libx86/SDL2_mixer.lib")

struct SDL_Texture;
struct Collider;

class ModuleJunis : public Module
{
public:
	ModuleJunis();
	~ModuleJunis();

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
	Animation backward;
	Animation run;
	Animation die;
	Animation touch;
	Animation shield;

	int Jlife = 3;

	Collider* player_collider;
	Collider* bullet_collider;

	iPoint position;
	iPoint screen_position;

	Mix_Chunk* JunisShot = nullptr;
	Mix_Chunk* JunisCollision = nullptr;

	bool alive = true;
	bool touched = false;
	int power_ups = 1;
};

#endif
