#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModuleTextures.h"
#include "Enemy.h"
#include "Enemy_Boss.h"
#include "Enemy_BlueNinja.h"
#include "Enemy_RedShip.h"
#include "ModuleMiko.h"
#include "ModuleSho.h"
#include "ModuleAudio.h"
#include "Enemy_GreenShip.h"
#include "Enemy_Samurai.h"
#include "Enemy_SeaShip.h"
#include "Enemy_MetalicGreen.h"
#include "Enemy_Fish.h"

#define SPAWN_MARGIN 10000

ModuleEnemies::ModuleEnemies()
{
	for(uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;
}

// Destructor
ModuleEnemies::~ModuleEnemies()
{
}

bool ModuleEnemies::Start()
{
	// Create a prototype for each enemy available so we can copy them around
	sprites = App->textures->Load("assets/tengai/Enemy.png");
	//Explosion = App->audio->LoadFx("assets/audio/Explosion.wav");

	return true;
}

update_status ModuleEnemies::PreUpdate()
{
	// check camera position to decide what to spawn
	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(queue[i].type != ENEMY_TYPES::NO_TYPE)
		{
			if(queue[i].x * SCREEN_SIZE < App->render->camera.x + (App->render->camera.w * SCREEN_SIZE) + SPAWN_MARGIN)
			{
				SpawnEnemy(queue[i]);
				queue[i].type = ENEMY_TYPES::NO_TYPE;
				LOG("Spawning enemy at %d", queue[i].x * SCREEN_SIZE);
			}
		}
	}

	return UPDATE_CONTINUE;
}

// Called before render is available
update_status ModuleEnemies::Update()
{
	for(uint i = 0; i < MAX_ENEMIES; ++i)
		if(enemies[i] != nullptr) enemies[i]->Move();

	for(uint i = 0; i < MAX_ENEMIES; ++i)
		if(enemies[i] != nullptr) enemies[i]->Draw(sprites);

	return UPDATE_CONTINUE;
}

update_status ModuleEnemies::PostUpdate()
{
	// check camera position to decide what to spawn
	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr)
		{
			if(enemies[i]->position.x * SCREEN_SIZE < (App->render->camera.x) - SPAWN_MARGIN)
			{
				LOG("DeSpawning enemy at %d", enemies[i]->position.x * SCREEN_SIZE);
				delete enemies[i];
				enemies[i] = nullptr;
			}
		}
	}
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleEnemies::CleanUp()
{
	LOG("Freeing all enemies");

	App->textures->Unload(sprites);

	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return true;
}

bool ModuleEnemies::AddEnemy(ENEMY_TYPES type, int x, int y)
{
	bool ret = false;

	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(queue[i].type == ENEMY_TYPES::NO_TYPE)
		{
			queue[i].type = type;
			queue[i].x = x;
			queue[i].y = y;
			ret = true;
			break;
		}
	}

	return ret;
}

void ModuleEnemies::SpawnEnemy(const EnemyInfo& info)
{
	// find room for the new enemy
	uint i = 0;
	for(; enemies[i] != nullptr && i < MAX_ENEMIES; ++i);

	if(i != MAX_ENEMIES)
	{
		switch(info.type)
		{
			case ENEMY_TYPES::BOSS:
			enemies[i] = new Enemy_Boss(info.x, info.y);
			break;

			case ENEMY_TYPES::RED_SHIP:
			enemies[i] = new Enemy_RedShip(info.x, info.y);
			break;

			case ENEMY_TYPES::BLUE_NINJA:
			enemies[i] = new Enemy_BlueNinja(info.x, info.y);
			break;

			case ENEMY_TYPES::GREEN_SHIP:
			enemies[i] = new Enemy_GreenShip(info.x, info.y);
			break;

			case ENEMY_TYPES::FISH:
			enemies[i] = new Enemy_Fish(info.x, info.y);
			break;

			case ENEMY_TYPES::METALIC_GREEN:
			enemies[i] = new Enemy_MetalicGreen(info.x, info.y);
			break;

			case ENEMY_TYPES::SAMURAI:
			enemies[i] = new Enemy_Samurai(info.x, info.y);
			break;

			case ENEMY_TYPES::SEA_SHIP:
			enemies[i] = new Enemy_SeaShip(info.x, info.y);
			break;
		}
	}
}

void ModuleEnemies::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
		{
			if ((c1->type == COLLIDER_TYPE::COLLIDER_ENEMY && c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_SHOT_P1)
				|| (c1->type == COLLIDER_TYPE::COLLIDER_ENEMY && c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_SHOT_P2))
			{
				enemies[i]->EnemyLife--;
				if (enemies[i]->EnemyLife <= 1)
				{
					//Mix_PlayChannel(-1, Explosion, 0);
					//Spawn at center of collider
					App->particles->AddParticle(App->particles->explosion,
						enemies[i]->position.x + enemies[i]->animation->GetCurrentFrame().w / 2,
						enemies[i]->position.y + enemies[i]->animation->GetCurrentFrame().h / 2);

					if (c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_SHOT_P1) {
						App->miko->score += 200;
					}
					else App->sho->score += 200;
					enemies[i]->alive = false;
					delete enemies[i];
					enemies[i] = nullptr;
				}
			}
			if ((c1->type == COLLIDER_TYPE::COLLIDER_ENEMY_GREEN && c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_SHOT_P1)
				|| (c1->type == COLLIDER_TYPE::COLLIDER_ENEMY_GREEN && c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_SHOT_P2))
			{
				enemies[i]->EnemyLife--;
				if (enemies[i]->EnemyLife <= 1)
				{
					//Mix_PlayChannel(-1, Explosion, 0);
					//Spawn at center of collider
					App->particles->AddParticle(App->particles->explosion,
						enemies[i]->position.x + enemies[i]->animation->GetCurrentFrame().w / 2,
						enemies[i]->position.y + enemies[i]->animation->GetCurrentFrame().h / 2);

					if (c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_SHOT_P1) {
						App->miko->score += 100;
					}
					else App->sho->score += 100;
					enemies[i]->alive = false;
					delete enemies[i];
					enemies[i] = nullptr;
				}
			}
			if ((c1->type == COLLIDER_TYPE::COLLIDER_ENEMY_RED && c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_SHOT_P1)
				|| (c1->type == COLLIDER_TYPE::COLLIDER_ENEMY_RED && c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_SHOT_P2))
			{
				enemies[i]->EnemyLife--;
				if (enemies[i]->EnemyLife <= 1)
				{
					//Mix_PlayChannel(-1, Explosion, 0);
					//Spawn at center of collider
					App->particles->AddParticle(App->particles->explosion,
						enemies[i]->position.x + enemies[i]->animation->GetCurrentFrame().w / 2,
						enemies[i]->position.y + enemies[i]->animation->GetCurrentFrame().h / 2);
					if (c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_SHOT_P1) {
						App->miko->score += 100;
					}
					else App->sho->score += 100;

					enemies[i]->PowerUp();
					enemies[i]->alive = false;
					delete enemies[i];
					enemies[i] = nullptr;
				}
			}
			if ((c1->type == COLLIDER_TYPE::COLLIDER_ENEMY_BOSS && c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_SHOT_P1)
				|| (c1->type == COLLIDER_TYPE::COLLIDER_ENEMY_BOSS && c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_SHOT_P2))
			{
				enemies[i]->EnemyLife--;
				if (enemies[i]->EnemyLife <= 1)
				{
					//Mix_PlayChannel(-1, Explosion, 0);
					//Spawn at center of collider
					App->particles->AddParticle(App->particles->explosion,
						enemies[i]->position.x + enemies[i]->animation->GetCurrentFrame().w / 2,
						enemies[i]->position.y + enemies[i]->animation->GetCurrentFrame().h / 2);
					if (c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_SHOT_P1) {
						App->miko->score += 8000;
					}
					else App->sho->score += 8000;
					enemies[i]->alive = false;
					delete enemies[i];
					enemies[i] = nullptr;
				}
			}
			if ((c1->type == COLLIDER_TYPE::COLLIDER_SAMURAI && c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_SHOT_P1)
				|| (c1->type == COLLIDER_TYPE::COLLIDER_SAMURAI && c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_SHOT_P2))
			{
				enemies[i]->EnemyLife--;
				if (enemies[i]->EnemyLife <= 1)
				{
					//Mix_PlayChannel(-1, Explosion, 0);
					//Spawn at center of collider
					App->particles->AddParticle(App->particles->explosion,
						enemies[i]->position.x + enemies[i]->animation->GetCurrentFrame().w / 2,
						enemies[i]->position.y + enemies[i]->animation->GetCurrentFrame().h / 2);
					if (c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_SHOT_P1) {
						App->miko->score += 1400;
					}
					else App->sho->score += 1400;
					enemies[i]->alive = false;
					delete enemies[i];
					enemies[i] = nullptr;
				}
			}
		}
	}

}