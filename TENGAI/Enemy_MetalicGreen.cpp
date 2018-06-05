#include "Application.h"
#include "ModuleParticles.h"
#include "Enemy_MetalicGreen.h"
#include "ModuleEnemies.h"
#include "ModuleCollision.h"
#include "ModuleInput.h"
#include "ModuleRender.h"

Enemy_MetalicGreen::Enemy_MetalicGreen(int x, int y) : Enemy(x, y)
{
	idle.PushBack({ 23,759,31,30 });
	idle.PushBack({ 79,759,31,31 });
	idle.PushBack({ 136,759,31,30 });
	idle.PushBack({ 188,759,31,30 });
	idle.PushBack({ 235,758,31,31 });
	idle.speed = 0.2f;
	
	animation = &idle;

	path.PushBack({ 1.0f, 0.0f }, 200, &idle);

	collider = App->collision->AddCollider({ x,y,32,38 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	position = iPoint(x, y);
	original_position = iPoint(x, y);
	EnemyLife = 2;
}

void Enemy_MetalicGreen::Move()
{
	/*if (position.x <= -App->render->camera.x / 2 + SCREEN_WIDTH + 40)
	{
		position = original_position + path.GetCurrentSpeed(&animation);
	}
	else if (position.x <= -App->render->camera.x / 2)
	{
		position = original_position + path2.GetCurrentSpeed(&animation);
	}*/
	position = original_position + path.GetCurrentSpeed(&animation);
}