#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");
	graphics = App->textures->Load("tengai/spritesheet.png");

	 //START BUTTON

	start.anim.PushBack({ 35,337,196,39 });
	start.anim.PushBack({ 5,158,196,39 });
	start.anim.loop = true;
	start.anim.speed = 0.5f;

	Mshot.anim.PushBack({ 11,50,10,12 });
	Mshot.anim.PushBack({ 34,50,11,11 });
	Mshot.anim.PushBack({ 58,51,11,10 });
	Mshot.anim.PushBack({ 82,51,12,10 });
	Mshot.anim.PushBack({ 106,53,11,6 });
	/*Mshot.anim.PushBack({ 129,49,12,14 });
	Mshot.anim.PushBack({ 153,49,14,14 });
	Mshot.anim.PushBack({ 177,49,14,13 });
	Mshot.anim.PushBack({ 201,50,14,12 });
	Mshot.anim.PushBack({ 225,52,13,7 });
	Mshot.anim.PushBack({ 249,49,12,14 });
	Mshot.anim.PushBack({ 273,49,14,14 });
	Mshot.anim.PushBack({ 297,49,14,13 });
	Mshot.anim.PushBack({ 321,50,14,12 });
	Mshot.anim.PushBack({ 345,52,13,17 });*/
	Mshot.anim.loop = true;
	Mshot.anim.speed = 0.4f;
	Mshot.speed = iPoint(10, 0);
	Mshot.life = 150000;

	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);

	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}

	return true;
}

// Update: draw background
update_status ModuleParticles::Update()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* p = active[i];

		if(p == nullptr)
			continue;

		if(p->Update() == false)
		{
			delete p;
			active[i] = nullptr;
		}
		else if(SDL_GetTicks() >= p->born)
		{
			App->render->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
			if(p->fx_played == false)
			{
				p->fx_played = true;
				// Play particle fx here
			}
		}
	}

	return UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, Uint32 delay)
{
	Particle* p = new Particle(particle);
	p->born = SDL_GetTicks() + delay;
	p->position.x = x;
	p->position.y = y;

	active[last_particle++] = p;
}

// -------------------------------------------------------------
// -------------------------------------------------------------

Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) : 
anim(p.anim), position(p.position), speed(p.speed),
fx(p.fx), born(p.born), life(p.life)
{}

bool Particle::Update()
{
	bool ret = true;

	if(life > 0)
	{
		if((SDL_GetTicks() - born) > life)
			ret = false;
	}
	else
		if(anim.Finished())
			ret = false;

	position.x += speed.x;
	position.y += speed.y;

	return ret;
}