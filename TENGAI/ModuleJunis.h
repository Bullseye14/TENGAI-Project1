#ifndef __ModuleJunis_H__
#define __ModuleJunis_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "Path.h"
#include "SDL_mixer/include/SDL_mixer.h"
#include "SDL\include\SDL_joystick.h"
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
	bool Shield();
	void Die();
	void Win();
	void Friend();

	bool Shield_Animation = false;
	bool Die_Animation = false;
	bool Spawn_Animation = false;
	void OnCollision(Collider* c1, Collider* c2);

public:

	Animation* AnimSocrates = nullptr;
	Animation SocratesApp, SocratesIdle;
	SDL_Texture* graphics = nullptr;
	SDL_Texture* graphics2 = nullptr;
	int score_x = 10;
	int score_y = 10;
	int font_score = -1;
	int font_players = -1;
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
	iPoint socrates_pos;
	Path path_socrates;
	Path path_die;
	Path path_win;
	Path path_spawn;

	Mix_Chunk* JunisShot = nullptr;
	Mix_Chunk* JunisCollision = nullptr;
	Mix_Chunk* JunisPowerUp = nullptr;
	Mix_Chunk* JunisPowerDown = nullptr;
	Mix_Chunk* SocratesAttack = nullptr;

	bool alive = true;
	bool won = false;
	int speed = 3;
	int power_ups = 1;
	int JunisLife = 1;
};

#endif
