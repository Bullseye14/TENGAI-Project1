#ifndef __MODULEPARTICLES_H__
#define __MODULEPARTICLES_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleCollision.h"

#define MAX_ACTIVE_PARTICLES 100

struct SDL_Texture;
struct Collider;
enum COLLIDER_TYPE;

struct Particle
{
	Collider* collider = nullptr;
	Animation anim;
	uint fx = 0;
	iPoint position;
	iPoint speed;
	Uint32 born = 0;
	Uint32 life = 0;
	bool fx_played = false;

	Particle();
	Particle(const Particle& p);
	bool Update();
};

class ModuleParticles : public Module
{
public:
	ModuleParticles();
	~ModuleParticles();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

	void AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type = COLLIDER_NONE, Uint32 delay = 0);

private:

	SDL_Texture* graphics = nullptr;
	SDL_Texture* graphics2 = nullptr;
	Particle* active[MAX_ACTIVE_PARTICLES];
	uint last_particle = 0;

public:

	Particle Mshot;
	Particle Jshot;
	Particle blueShot;
	Particle Eshot1;
	Particle Eshot2;
	Particle Eshot3;
	Particle Eshot4;
	Particle Eshot5;
	Particle Eshot6;
	Particle Eshot7;
	Particle Eshot8;
	Particle Eshot9;
	Particle Eshot10;
	Particle Eshot11;
	Particle Eshot12;
	/*Particle Eshot13;
	Particle Eshot14;
	Particle Eshot15;
	Particle Eshot16;*/
	Particle power_down;
	Particle power_up;
	Particle explosion;

	Particle start;
};

#endif // __MODULEPARTICLES_H__