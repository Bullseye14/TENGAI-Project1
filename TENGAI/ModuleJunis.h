#ifndef __ModuleJunis_H__
#define __ModuleJunis_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "Path.h"
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

	bool Spawn();
	void Die();

	bool Shield_Animation = false;
	bool Die_Animation = false;
	bool Spawn_Animation = false;
	void OnCollision(Collider* c1, Collider* c2);

public:

	SDL_Texture* graphics = nullptr;
	int font_score = -1;
	char score_text[10];
	uint score = 0;
	Animation* current_animation = nullptr;
	Animation idle;
	Animation touch;
	Animation backward;
	Animation run;
	Animation die;
	Animation shield;

	Collider* player_collider;
	Collider* bullet_collider;

	iPoint position;
	Path path_die;
	Path path_spawn;

	Mix_Chunk* JunisShot = nullptr;
	Mix_Chunk* JunisCollision = nullptr;

	bool alive = true;
	int speed = 3;
	int power_ups = 1;
	int Jlife = 3;
	int JunisLife = 1;
};

#endif
