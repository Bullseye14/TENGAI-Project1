#ifndef __ModuleSho_H__
#define __ModuleSho_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment(lib,"SDL_mixer/libx86/SDL2_mixer.lib")

struct SDL_Texture;
struct Collider;

class ModuleSho : public Module
{
public:
	ModuleSho();
	~ModuleSho();

	bool Start();
	update_status Update();
	bool CleanUp();

	bool Shield_Animation = false;
	void OnCollision(Collider* c1, Collider* c2);

public:

	SDL_Texture* graphics = nullptr;

	Animation* current_animation = nullptr;
	Animation idle;
	Animation backward;
	Animation run;
	Animation die;
	Animation shield;

	Collider* player_collider;
	Collider* bullet_collider;

	iPoint position;
	iPoint screen_position;

	Mix_Chunk* ShosShot = nullptr;
	Mix_Chunk* ShoCollision = nullptr;
};

#endif
