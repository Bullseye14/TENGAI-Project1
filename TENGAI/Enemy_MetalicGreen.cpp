#include "Application.h"
#include "ModuleParticles.h"
#include "Enemy_MetalicGreen.h"
#include "ModuleEnemies.h"
#include "ModuleCollision.h"
#include "ModuleInput.h"
#include "ModuleRender.h"

Enemy_MetalicGreen::Enemy_MetalicGreen(int x, int y) : Enemy(x, y)
{
	idle.PushBack({ 34,99,29,23 });
	idle.PushBack({ 85,99,30,23 });
	idle.PushBack({ 133,99,31,23 });
	idle.speed = 0.2f;

	animation = &idle;

	collider = App->collision->AddCollider({ x,y,32,38 }, COLLIDER_TYPE::COLLIDER_ENEMY_RED, (Module*)App->enemies);
	position = iPoint(x, y);
	original_position = iPoint(x, y);
	EnemyLife = 2;
}

void Enemy_MetalicGreen::Move()
{
	if (position.x <= -App->render->camera.x / 2 + SCREEN_WIDTH + 40)
	{
		position = original_position + path.GetCurrentSpeed(&animation);
	}
	else if (position.x <= -App->render->camera.x / 2)
	{
		position = original_position + path2.GetCurrentSpeed(&animation);
	}
}