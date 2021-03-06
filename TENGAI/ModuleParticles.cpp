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

	BasaroShot.anim.PushBack({ 357,12,15,15 });
	BasaroShot.anim.PushBack({ 381,12,15,15 });
	BasaroShot.anim.PushBack({ 258,77,15,15 });
	BasaroShot.anim.PushBack({ 282,77,15,15 });
	BasaroShot.anim.PushBack({ 306,77,15,15 });
	BasaroShot.anim.PushBack({ 330,77,15,15 });
	BasaroShot.anim.PushBack({ 354,77,15,15 });
	BasaroShot.anim.PushBack({ 378,77,15,15 });
	BasaroShot.anim.speed = 1.0f;
	BasaroShot.speed = iPoint(7, 0);
	BasaroShot.life = 500;

	SocratesShot1.anim.PushBack({ 53,38,8,8 });
	SocratesShot1.speed = iPoint(7, -2);
	SocratesShot1.life = 500;

	SocratesShot2.anim.PushBack({ 53,38,8,8 });
	SocratesShot2.speed = iPoint(7, 2);
	SocratesShot2.life = 500;

	blueShot.anim.PushBack({ 24,204,7,7 });
	blueShot.anim.PushBack({ 36,203,9,9 });
	blueShot.anim.PushBack({ 49,203,9,9 });
	blueShot.anim.PushBack({ 62,203,9,9 });
	blueShot.anim.PushBack({ 76,204,7,7 });
	blueShot.anim.speed = 1.0f;
	blueShot.speed = iPoint(-3, 0);
	blueShot.life = 2000;

	Eshot1.anim.PushBack({ 428,48,6,6 });
	Eshot1.anim.PushBack({ 439,48,6,6 });
	Eshot1.anim.PushBack({ 451,48,6,6 });
	Eshot1.anim.speed = 0.3f;
	Eshot1.speed = iPoint(-3, 0);
	Eshot1.life = 2000;

	Eshot2.anim.PushBack({ 428,48,6,6 });
	Eshot2.anim.PushBack({ 439,48,6,6 });
	Eshot2.anim.PushBack({ 451,48,6,6 });
	Eshot2.anim.speed = 0.3f;
	Eshot2.speed = iPoint(2, 1);
	Eshot2.life = 2000;

	Eshot3.anim.PushBack({ 428,48,6,6 });
	Eshot3.anim.PushBack({ 439,48,6,6 });
	Eshot3.anim.PushBack({ 451,48,6,6 });
	Eshot3.anim.speed = 0.3f;
	Eshot3.speed = iPoint(1, 2);
	Eshot3.life = 2000;

	Eshot4.anim.PushBack({ 428,48,6,6 });
	Eshot4.anim.PushBack({ 439,48,6,6 });
	Eshot4.anim.PushBack({ 451,48,6,6 });
	Eshot4.anim.speed = 0.3f;
	Eshot4.speed = iPoint(0, 3);
	Eshot4.life = 2000;

	Eshot5.anim.PushBack({ 428,48,6,6 });
	Eshot5.anim.PushBack({ 439,48,6,6 });
	Eshot5.anim.PushBack({ 451,48,6,6 });
	Eshot5.anim.speed = 0.3f;
	Eshot5.speed = iPoint(-0.67, 2);
	Eshot5.life = 2000;

	Eshot6.anim.PushBack({ 428,48,6,6 });
	Eshot6.anim.PushBack({ 439,48,6,6 });
	Eshot6.anim.PushBack({ 451,48,6,6 });
	Eshot6.anim.speed = 0.3f;
	Eshot6.speed = iPoint(-1.33, 1);
	Eshot6.life = 2000;

	Eshot7.anim.PushBack({ 428,48,6,6 });
	Eshot7.anim.PushBack({ 439,48,6,6 });
	Eshot7.anim.PushBack({ 451,48,6,6 });
	Eshot7.anim.speed = 0.3f;
	Eshot7.speed = iPoint(-2, 0);
	Eshot7.life = 2000;

	Eshot8.anim.PushBack({ 428,48,6,6 });
	Eshot8.anim.PushBack({ 439,48,6,6 });
	Eshot8.anim.PushBack({ 451,48,6,6 });
	Eshot8.anim.speed = 0.3f;
	Eshot8.speed = iPoint(-1.33, -1);
	Eshot8.life = 2000;
	
	Eshot8.anim.PushBack({ 83,82,5,7 });
	Eshot8.anim.PushBack({ 98,82,6,5 });
	Eshot8.anim.PushBack({ 113,83,7,5 });
	Eshot8.anim.PushBack({ 129,83,7,5 });
	Eshot8.anim.speed = 0.3f;
	Eshot8.speed = iPoint(-0.67, -2);
	Eshot8.life = 2000;

	Eshot9.anim.PushBack({ 83,82,5,7 });
	Eshot9.anim.PushBack({ 98,82,6,5 });
	Eshot9.anim.PushBack({ 113,83,7,5 });
	Eshot9.anim.PushBack({ 129,83,7,5 });
	Eshot9.anim.speed = 0.3f;
	Eshot9.speed = iPoint(0, -3);
	Eshot9.life = 2000;

	Eshot10.anim.PushBack({ 83,82,5,7 });
	Eshot10.anim.PushBack({ 98,82,6,5 });
	Eshot10.anim.PushBack({ 113,83,7,5 });
	Eshot10.anim.PushBack({ 129,83,7,5 });
	Eshot10.anim.speed = 0.3f;
	Eshot10.speed = iPoint(1, -2);
	Eshot10.life = 2000;

	Eshot11.anim.PushBack({ 83,82,5,7 });
	Eshot11.anim.PushBack({ 98,82,6,5 });
	Eshot11.anim.PushBack({ 113,83,7,5 });
	Eshot11.anim.PushBack({ 129,83,7,5 });
	Eshot11.anim.speed = 0.3f;
	Eshot11.speed = iPoint(2, -1);
	Eshot11.life = 2000;

	Eshot12.anim.PushBack({ 83,82,5,7 });
	Eshot12.anim.PushBack({ 98,82,6,5 });
	Eshot12.anim.PushBack({ 113,83,7,5 });
	Eshot12.anim.PushBack({ 129,83,7,5 });
	Eshot12.anim.speed = 0.3f;
	Eshot12.speed = iPoint(3, 0);
	Eshot12.life = 2000;

	/*Eshot13.anim.PushBack({ 83,82,5,7 });
	Eshot13.anim.PushBack({ 98,82,6,5 });
	Eshot13.anim.PushBack({ 113,83,7,5 });
	Eshot13.anim.PushBack({ 129,83,7,5 });
	Eshot13.anim.speed = 0.3f;
	Eshot13.speed = iPoint(-2, 0);
	Eshot13.life = 2000;

	Eshot14.anim.PushBack({ 83,82,5,7 });
	Eshot14.anim.PushBack({ 98,82,6,5 });
	Eshot14.anim.PushBack({ 113,83,7,5 });
	Eshot14.anim.PushBack({ 129,83,7,5 });
	Eshot14.anim.speed = 0.3f;
	Eshot14.speed = iPoint(-2, 0);
	Eshot14.life = 2000;

	Eshot15.anim.PushBack({ 83,82,5,7 });
	Eshot15.anim.PushBack({ 98,82,6,5 });
	Eshot15.anim.PushBack({ 113,83,7,5 });
	Eshot15.anim.PushBack({ 129,83,7,5 });
	Eshot15.anim.speed = 0.3f;
	Eshot15.speed = iPoint(-2, 0);
	Eshot15.life = 2000;

	Eshot16.anim.PushBack({ 83,82,5,7 });
	Eshot16.anim.PushBack({ 98,82,6,5 });
	Eshot16.anim.PushBack({ 113,83,7,5 });
	Eshot16.anim.PushBack({ 129,83,7,5 });
	Eshot16.anim.speed = 0.3f;
	Eshot16.speed = iPoint(-2, 0);
	Eshot16.life = 2000;*/
	
	Mshot.anim.PushBack({ 0,13,10,12 });
	Mshot.anim.PushBack({ 23,13,11,11 });
	Mshot.anim.PushBack({ 47,14,11,10 });
	Mshot.anim.PushBack({ 71,14,12,10 });
	Mshot.anim.PushBack({ 95,16,11,6 });
	Mshot.anim.speed = 0.4f;
	Mshot.speed = iPoint(10, 0);
	Mshot.life = 500;

	Jshot.anim.PushBack({ 8,38,30,8 });
	Jshot.anim.PushBack({ 8,55,30,8 });
	Jshot.anim.PushBack({ 47,55,30,8 });
	Jshot.anim.speed = 0.4f;
	Jshot.speed = iPoint(10, 0);
	Jshot.life = 500;

	
	power_up.anim.PushBack({ 497,7,30,21 });
	power_up.anim.PushBack({ 535,7,30,21 });
	power_up.anim.PushBack({ 572,7,30,21 });
	power_up.anim.PushBack({ 608,7,30,21 });
	power_up.anim.PushBack({ 646,7,30,21 });
	power_up.anim.PushBack({ 497,38,30,21 });
	power_up.anim.PushBack({ 535,38,30,21 });
	power_up.anim.PushBack({ 572,38,30,21 });
	power_up.anim.PushBack({ 608,38,30,21 });
	power_up.anim.PushBack({ 646,38,30,21 });
	power_up.anim.PushBack({ 497,69,30,21 });
	power_up.anim.PushBack({ 535,69,30,21 });
	power_up.anim.PushBack({ 572,69,30,21 });
	power_up.anim.PushBack({ 608,69,30,21 });
	power_up.anim.PushBack({ 646,69,30,21 });
	power_up.anim.PushBack({ 497,101,30,21 });
	power_up.anim.speed = 0.1f;
	power_up.life = 3000;

	explosion.anim.PushBack({ 2,240,45,43 });
	explosion.anim.PushBack({ 59,235,47,53 });
	explosion.anim.PushBack({ 118,234,53,60 });
	explosion.anim.PushBack({ 180,237,49,56 });
	explosion.anim.PushBack({ 242,235,52,59 });
	explosion.anim.PushBack({ 304,235,51,62 });
	explosion.anim.PushBack({ 365,235,52,63 });
	explosion.anim.PushBack({ 432,235,55,62 });
	explosion.anim.PushBack({ 499,235,55,63 });
	explosion.anim.PushBack({ 566,234,52,59 });
	explosion.anim.PushBack({ 632,234,51,58 });
	explosion.anim.PushBack({ 1,1,1,1 });
	explosion.anim.speed = 0.19f;
	explosion.anim.loop = false;
	


	// TO PRECISE, per arreglar a partir daqui//
	Shoshot.anim.PushBack({ 71,363,26,3 });
	Shoshot.anim.PushBack({ 105,363,31,4 });
	Shoshot.anim.PushBack({ 46,363,31,3 });
	Shoshot.anim.speed = 0.4f;
	Shoshot.speed = iPoint(10, 0);
	Shoshot.life = 500;

	Shosfriend.anim.PushBack({ 189,358,23,13 });
	Shosfriend.anim.PushBack({ 224,358,32,13 });
	Shosfriend.anim.PushBack({ 266,358,32,13 });
	Shosfriend.anim.PushBack({ 307,358,32,13 });
	Shosfriend.anim.speed = 0.3f;
	Shosfriend.speed = iPoint(10, 0);
	Shosfriend.life = 2000;

	P_U.anim.PushBack({ 496,128,26,15 });
	P_U.anim.PushBack({ 496,140,26,15 });
	P_U.anim.PushBack({ 496,158,26,15 });
	P_U.anim.speed = 0.1f;
	P_U.life = 3000;
	
	P_D.anim.PushBack({ 529,140,26,15 });
	P_D.anim.PushBack({ 529,158,26,15 });
	P_D.anim.speed = 0.1f;
	P_D.life = 3000;
	
	_100.anim.PushBack({ 560,147,9,7 });
	_100.anim.PushBack({ 560,157,9,7 });
	_100.anim.PushBack({ 560,167,9,7 });
	_100.anim.speed = 0.1f;
	_100.life = 3000;
	
	_500.anim.PushBack({ 94,36,11,7 });
	_500.anim.PushBack({ 94,27,11,7 });
	_500.anim.PushBack({ 94,18,11,7 });
	_500.anim.speed = 0.1f;
	_500.life = 3000;
	
	_200.anim.PushBack({ 80,36,11,7 });
	_200.anim.PushBack({ 80,27,11,7 });
	_200.anim.PushBack({ 80,18,11,7 });
	_200.anim.speed = 0.1f;
	_200.life = 3000;
	
	_1000.anim.PushBack({ 108,36,13,7 });
	_1000.anim.PushBack({ 108,27,13,7 });
	_1000.anim.PushBack({ 108,18,13,7 });
	_1000.anim.speed = 0.1f;
	_1000.life = 3000;
	
	_2000.anim.PushBack({ 124,36,15,7 });
	_2000.anim.PushBack({ 124,27,15,7 });
	_2000.anim.PushBack({ 124,18,15,7 });
	_2000.anim.speed = 0.1f;
	_2000.life = 3000;
	
	_4000.anim.PushBack({ 142,36,15,7 });
	_4000.anim.PushBack({ 142,27,15,7 });
	_4000.anim.PushBack({ 142,18,15,7 });
	_4000.anim.speed = 0.1f;
	_4000.life = 3000;

	Mlife.anim.PushBack({385,320,20,20});
	Slife.anim.PushBack({ 385,352,20,20 });

}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");
	graphics = App->textures->Load("assets/tengai/ParticlesSpritesheet.png");

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
			if (p->collider) 	p->collider->to_delete = true;
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

	//friends speed
	if (collider != nullptr && collider->type == COLLIDER_TYPE::COLLIDER_PLAYER_SHOT_P1) {

	}
	position.x += speed.x;
	position.y += speed.y;

	//Aixi no peta amb molts dispars pero desparaeix el collider en comptes de petar
	if (collider != nullptr && collider->type != COLLIDER_NONE)
		collider->SetPos(position.x, position.y);

	return ret;
}

bool Particle::InScreen() {
	return position.x <= SCREEN_WIDTH && position.x >= 0 &&
		position.y <= SCREEN_HEIGHT && position.y >= 0;
}