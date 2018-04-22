#include "Application.h"
#include "ModuleParticles.h"
#include "Enemy_Boss.h"
#include "ModuleEnemies.h"
#include "ModuleSceneForest.h"
#include "ModuleCollision.h"
#include "ModuleInput.h"
#include "ModuleRender.h"

Enemy_Boss::Enemy_Boss(int x, int y) : Enemy(x, y)
{
	path2.PushBack({ 0.0, 0.0f }, 550, &idle);

	path.PushBack({ 1.0f, -0.25f }, 100, &idle);
	path.PushBack({ 1.0f, 0.25f }, 100, &open);
	path.PushBack({ 1.0f, 0.0f }, 1, &shot);
	path.PushBack({ 1.0f, 0.0f }, 50, &aftershot);
	path.PushBack({ 1.0f, -0.25f }, 100, &close);
	path.PushBack({ 1.0f, 0.25f }, 100, &idle);
	path.loop = true;
	
	//idle
	idle.PushBack({ 43,138,91,107 });
	idle.PushBack({ 157,140,96,109 });
	idle.PushBack({ 253,143,93,107 });
	idle.PushBack({ 362,145,93,108 });
	idle.PushBack({ 38,261,91,108 });
	idle.PushBack({ 133,259,88,110 });
	idle.PushBack({ 240,267,98,101 });
	idle.loop = true;
	idle.speed = 0.15f;
	//open
	open.PushBack({ 359,267,98,101 });
	open.PushBack({ 6,383,97,102 });
	open.PushBack({ 104,375,97,113 });
	open.PushBack({ 202,371,97,121 });
	open.PushBack({ 309,369,97,130 });
	open.PushBack({ 412,401,98,133 });
	open.PushBack({ 412,401,98,133 });
	open.PushBack({ 412,401,98,133 });
	open.PushBack({ 412,401,98,133 });
	open.loop = false;
	open.speed = 0.15f;
	//shot
	shot.PushBack({ 412,401,98,133 });
	shot.loop = false;
	//aftershot
	aftershot.PushBack({ 412,401,98,133 });
	//close
	close.PushBack({ 309,369,97,130 });
	close.PushBack({ 202,371,97,121 });
	close.PushBack({ 104,375,97,113 });
	close.PushBack({ 6,383,97,102 });
	close.PushBack({ 359,267,98,101 });
	close.loop = false;
	close.speed = 0.15f;

	// die animation 
	die.PushBack({ 43,44,91,107 });
	die.PushBack({ 1,1,1,1 });
	die.PushBack({ 43,44,91,107 });
	die.PushBack({ 1,1,1,1 });
	die.PushBack({ 43,44,91,107 });
	die.PushBack({ 1,1,1,1 });
	die.PushBack({ 43,44,91,107 });
	die.PushBack({ 1,1,1,1 });
	die.PushBack({ 43,44,91,107 });
	die.PushBack({ 1,1,1,1 });
	die.loop = false;
	die.speed = 0.1f;

	animation = &idle; 
	
	collider = App->collision->AddCollider({ x,y,100,150 }, COLLIDER_TYPE::COLLIDER_ENEMY_BOSS, (Module*)App->enemies);

	original_position = iPoint(x,y);
	
	EnemyLife = 100;
}

void Enemy_Boss::Shoot() 
{
	App->particles->AddParticle(App->particles->Eshot1, position.x + 48, position.y + animation->GetCurrentFrame().h / 2, COLLIDER_ENEMY_SHOT, 0.5f);
	App->particles->AddParticle(App->particles->Eshot2, position.x + 48, position.y + animation->GetCurrentFrame().h / 2, COLLIDER_ENEMY_SHOT, 0.5f);
	App->particles->AddParticle(App->particles->Eshot3, position.x + 48, position.y + animation->GetCurrentFrame().h / 2, COLLIDER_ENEMY_SHOT, 0.5f);
	App->particles->AddParticle(App->particles->Eshot4, position.x + 48, position.y + animation->GetCurrentFrame().h / 2, COLLIDER_ENEMY_SHOT, 0.5f);
	App->particles->AddParticle(App->particles->Eshot5, position.x + 48, position.y + animation->GetCurrentFrame().h / 2, COLLIDER_ENEMY_SHOT, 0.5f);
	App->particles->AddParticle(App->particles->Eshot6, position.x + 48, position.y + animation->GetCurrentFrame().h / 2, COLLIDER_ENEMY_SHOT, 0.5f);
	App->particles->AddParticle(App->particles->Eshot7, position.x + 48, position.y + animation->GetCurrentFrame().h / 2, COLLIDER_ENEMY_SHOT, 0.5f);
	App->particles->AddParticle(App->particles->Eshot8, position.x + 48, position.y + animation->GetCurrentFrame().h / 2, COLLIDER_ENEMY_SHOT, 0.5f);
	App->particles->AddParticle(App->particles->Eshot9, position.x + 48, position.y + animation->GetCurrentFrame().h / 2, COLLIDER_ENEMY_SHOT, 0.5f);
	App->particles->AddParticle(App->particles->Eshot10, position.x + 48, position.y + animation->GetCurrentFrame().h / 2, COLLIDER_ENEMY_SHOT, 0.5f);
	App->particles->AddParticle(App->particles->Eshot11, position.x + 48, position.y + animation->GetCurrentFrame().h / 2, COLLIDER_ENEMY_SHOT, 0.5f);
	App->particles->AddParticle(App->particles->Eshot12, position.x + 48, position.y + animation->GetCurrentFrame().h / 2, COLLIDER_ENEMY_SHOT, 0.5f);
}

void Enemy_Boss::Die() 
{
	animation = &die;
}

void Enemy_Boss::Move()
{
	if (App->input->keyboard[SDL_SCANCODE_2] == KEY_STATE::KEY_DOWN)
	{
		Shoot();
	}
	if (animation == &shot) { Shoot(); }

	if (EnemyLife==1) 
	{
		Die();
	}
	
	if (position.x <= -App->render->camera.x / 2 + SCREEN_WIDTH - 150) 
	{
		position = original_position + path.GetCurrentSpeed(&animation);
	}
	else 
	{
		position = original_position + path2.GetCurrentSpeed(&animation);
	}
	
	
}