#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleEnemy.h"
#include "ModuleAudio.h"

ModuleEnemy::ModuleEnemy()
{
	enemy1 = NULL;
	current_animation = NULL;

	enemy_pos.x = 0;
	enemy_pos.y = 120;

	offsetCamera = 3;

	//animation
	enemyAnim.PushBack{ (43,44,91,107) };

}

ModuleEnemy::~ModuleEnemy() {}

bool ModuleEnemy::Start()
{
	LOG("Loading player");

	enemy1 = App->textures->Load("tengai/enemy.png");

	enemy_pos.x = 70;
	enemy_pos.y = 60;

	enemy_collider = App->collision->AddCollider({ enemy_pos.x,enemy_pos.y,91,107 }, COLLIDER_ENEMY);

	return true;
}

bool ModuleEnemy::CleanUp()
{
	LOG("Unloading");

	App->textures->Unload(enemy1);

	return true;
}

update_status ModuleEnemy::Update()
{
	enemy_collider->SetPos(enemy_pos.x, enemy_pos.y);

	App->render->Blit(enemy1, enemy_pos.x, enemy_pos.y, &(current_animation->GetCurrentFrame()));

	return UPDATE_CONTINUE;
}

void ModuleEnemy::OnCollision(Collider* c1, Collider* c2)
{
	int a = 1;
}