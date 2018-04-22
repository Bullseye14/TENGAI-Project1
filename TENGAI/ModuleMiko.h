#ifndef __ModuleMiko_H__
#define __ModuleMiko_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "Path.h"
#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment(lib,"SDL_mixer/libx86/SDL2_mixer.lib")

struct SDL_Texture;
struct Collider;

class ModuleMiko : public Module
{
public:
	ModuleMiko();
	~ModuleMiko();

	bool Start();
	update_status Update();
	bool CleanUp();

	bool Spawn();
	bool Shield();
	void Die();
	void Win();
	void Friend();

	bool Shield_Animation = false;
	bool Die_Animation = false;
	bool Spawn_Animation = false;
	void OnCollision(Collider* c1, Collider* c2);

public:

	Animation* Mikofriend = nullptr;
	SDL_Texture * graphics = nullptr;
	int score_x = 60;
	int font_score = -1;
	int font_players = -1;
	char score_text[10];
	uint score = 0;

	Animation* current_animation = nullptr;
	Animation friendApp;
	Animation friendIdle;
	Animation idle;
	Animation touch;
	Animation backward;
	Animation run;
	Animation die;
	Animation shield;

	Collider* player_collider;
	Collider* bullet_collider;

	iPoint position;
	iPoint mikofr;
	Path path_friend;
	Path path_die;
	Path path_win;
	Path path_spawn;

	Mix_Chunk* MikosShot = nullptr;
	Mix_Chunk* MikoCollision = nullptr;
	Mix_Chunk* MikoPowerUp = nullptr;
	Mix_Chunk* MikoPowerDown = nullptr;
	Mix_Chunk* MikoFriendAttack = nullptr;


	bool alive = true;
	bool won = false;
	int speed = 3;
	int power_ups = 1;
	int Mlife = 3;
	int MikoLife = 1;
};

#endif