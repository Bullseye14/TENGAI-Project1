#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;

	start.anim.PushBack({ 35,337,196,39 });
	start.anim.PushBack({ 5,158,196,39 });
	start.anim.speed = 0.5f;

	Eshot.anim.PushBack({ 83,82,5,7 });
	Eshot.anim.PushBack({ 98,82,6,5 });
	Eshot.anim.PushBack({ 113,83,7,5 });
	Eshot.anim.PushBack({ 129,83,7,5 });
	Eshot.anim.speed = 0.3f;
	Eshot.speed = iPoint(-2, 0);
	Eshot.life = 2000;
	
	Mshot.anim.PushBack({ 0,13,10,12 });
	Mshot.anim.PushBack({ 23,13,11,11 });
	Mshot.anim.PushBack({ 47,14,11,10 });
	Mshot.anim.PushBack({ 71,14,12,10 });
	Mshot.anim.PushBack({ 95,16,11,6 });
	Mshot.anim.speed = 0.4f;
	Mshot.speed = iPoint(10, 0);
	Mshot.life = 1500;

	Jshot.anim.PushBack({ 8,38,30,8 });
	Jshot.anim.PushBack({ 8,55,30,8 });
	Jshot.anim.PushBack({ 47,55,30,8 });
	Jshot.anim.speed = 0.4f;
	Jshot.speed = iPoint(10, 0);
	Jshot.life = 1500;

}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");
	graphics = App->textures->Load("tengai/ParticlesSpritesheet.png");

	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);
	App->textures->Unload(graphics2);

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
			p->collider->to_delete = true;
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

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] == nullptr)
		{
			Particle* p = new Particle(particle);
			p->born = SDL_GetTicks() + delay;
			p->position.x = x;
			p->position.y = y;
			if (collider_type != COLLIDER_NONE)
				p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), collider_type, this);
			active[i] = p;
			break;
			active[last_particle++] = p;
		}
	}
}

// -------------------------------------------------------------
void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (active[i] != nullptr && active[i]->collider == c1)
		{
			active[i]->collider->to_delete = true;
			delete active[i];
			active[i] = nullptr;
			break;
		}
	}
}
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

	//Aixi no peta amb molts dispars pero desparaeix el collider en comptes de petar
	if (collider != nullptr && collider->type != COLLIDER_NONE)
		collider->SetPos(position.x, position.y);

	return ret;
}