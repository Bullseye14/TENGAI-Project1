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
	idle.PushBack({ 362,51,93,108 });
	idle.PushBack({ 38,167,91,108 });
	idle.PushBack({ 133,165,88,110 });
	idle.PushBack({ 240,173,98,101 });
	idle.PushBack({ 359,173,98,101 });
	idle.PushBack({ 6,289,97,102 });
	idle.PushBack({ 104,281,97,113 });
	idle.PushBack({ 202,277,97,121 });
	idle.PushBack({ 309,275,97,130 });
	idle.PushBack({ 408,271,98,133 });
	idle.PushBack({ 309,275,97,130 });
	idle.PushBack({ 202,277,97,121 });
	idle.PushBack({ 104,281,97,113 });
	idle.PushBack({ 6,289,97,102 });
	idle.PushBack({ 359,173,98,101 });
	idle.PushBack({ 240,173,98,101 });
	idle.PushBack({ 133,165,88,110 });
	idle.PushBack({ 38,167,91,108 });
	idle.PushBack({ 362,51,93,108 });
	idle.PushBack({ 253,49,93,107 });
	idle.PushBack({ 157,46,96,109 });
	idle.loop = true;
	idle.speed = 0.19f;
}

ModuleEnemy::~ModuleEnemy() {}

bool ModuleEnemy::Start()
{
	LOG("Loading player");

	enemy1 = App->textures->Load("tengai/Enemy.png");

	enemy_collider = App->collision->AddCollider({ enemy_pos.x,enemy_pos.y,100,20 }, COLLIDER_ENEMY, this);
	enemy_collider1 = App->collision->AddCollider({ enemy_pos.x,enemy_pos.y,66,37 }, COLLIDER_ENEMY, this);
	enemy_collider2 = App->collision->AddCollider({ enemy_pos.x,enemy_pos.y,69,75 }, COLLIDER_ENEMY, this);

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

	enemy_collider->SetPos(enemy_pos.x, enemy_pos.y + 37);
	enemy_collider1->SetPos(enemy_pos.x + 15, enemy_pos.y);
	enemy_collider2->SetPos(enemy_pos.x + 12, enemy_pos.y + 57);
	
	/*if (App->input->keyboard[SDL_SCANCODE_E] == KEY_STATE::KEY_IDLE) {
		App->particles->AddParticle(App->particles->Mshot, enemy_pos.x - 31, enemy_pos.y + 6, COLLIDER_ENEMY_SHOT);
	}*/

	App->render->Blit(enemy1, enemy_pos.x, enemy_pos.y, &(current_animation->GetCurrentFrame()));

	return UPDATE_CONTINUE;
}

void ModuleEnemy::OnCollision(Collider* c1, Collider* c2)
{
	int a = 1;
}