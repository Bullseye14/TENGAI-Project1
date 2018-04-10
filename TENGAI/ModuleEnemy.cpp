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

	enemy_pos.x = 220;
	enemy_pos.y = 10;

	offsetCamera = 3;

	//animation
	idle.PushBack({ 43,44,91,107 });
	idle.PushBack({ 157,46,96,109 });
	idle.PushBack({ 253,49,93,107 });
	/*idle.PushBack({ 157,46,96,109 });
	idle.PushBack({ 157,46,96,109 });
	idle.PushBack({ 157,46,96,109 });
	idle.PushBack({ 157,46,96,109 });
	idle.PushBack({ 157,46,96,109 });
	idle.PushBack({ 157,46,96,109 });
	idle.PushBack({ 157,46,96,109 });
	idle.PushBack({ 157,46,96,109 });
	idle.PushBack({ 157,46,96,109 });
	idle.PushBack({ 157,46,96,109 });*/
	idle.loop = true;
	idle.speed = 0.19f;
}

ModuleEnemy::~ModuleEnemy() {}

bool ModuleEnemy::Start()
{
	LOG("Loading player");

	enemy1 = App->textures->Load("tengai/Enemy.png");

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
	current_animation = &idle;

	enemy_collider->SetPos(enemy_pos.x, enemy_pos.y);

	App->render->Blit(enemy1, enemy_pos.x, enemy_pos.y, &(current_animation->GetCurrentFrame()));

	return UPDATE_CONTINUE;
}

void ModuleEnemy::OnCollision(Collider* c1, Collider* c2)
{
	int a = 1;
}