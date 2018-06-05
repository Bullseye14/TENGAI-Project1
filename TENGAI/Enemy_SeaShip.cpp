#include "Application.h"
#include "ModuleParticles.h"
#include "Enemy_SeaShip.h"
#include "ModuleEnemies.h"
#include "ModuleCollision.h"
#include "ModuleInput.h"
#include "ModuleRender.h"

Enemy_SeaShip::Enemy_SeaShip(int x, int y) : Enemy(x, y)
{
	path2.PushBack({ 0.0f,0.0f }, 5000, &idle);

	path.PushBack({ -3.0f, 0.0f }, 15, &idle);
	path.PushBack({ -2.5f, 0.0f }, 15, &idle);
	path.PushBack({ -2.0f, 0.0f }, 15, &idle);
	path.PushBack({ -1.5f, 0.0f }, 15, &idle);
	path.PushBack({ -1.0f, 0.0f }, 15, &idle);
	path.PushBack({ -0.5f, 0.0f }, 15, &idle);
	path.PushBack({ 0.0f, 0.0f }, 15, &idle);
	path.PushBack({ 1.0f, 0.0f }, 100, &idle);
	path.PushBack({ 1.5f, 0.0f }, 15, &idle);
	path.PushBack({ 2.0f, 0.0f }, 15, &idle);
	path.PushBack({ 2.5f, 0.0f }, 15, &idle);
	path.PushBack({ 3.0f, 0.0f }, 15, &idle);
	path.PushBack({ 3.5f, 0.0f }, 6000, &idle);

	idle.PushBack({ 255,433,35,38 });
	idle.PushBack({ 339,435,33,36 });
	idle.PushBack({ 417,435,33,34 });
	idle.speed = 0.2f;

	animation = &idle;

	collider = App->collision->AddCollider({ x,y,32,38 }, COLLIDER_TYPE::COLLIDER_ENEMY_RED, (Module*)App->enemies);
	position = iPoint(x, y);
	original_position = iPoint(x, y);
	EnemyLife = 2;
}

void Enemy_SeaShip::Move()
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