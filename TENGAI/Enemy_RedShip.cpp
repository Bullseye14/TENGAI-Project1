#include "Application.h"
#include "ModuleParticles.h"
#include "Enemy_RedShip.h"
#include "ModuleEnemies.h"
#include "ModuleCollision.h"
#include "ModuleInput.h"
#include "ModuleRender.h"

Enemy_RedShip::Enemy_RedShip(int x, int y) : Enemy(x, y)
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

	idle.PushBack({ 85,475,32,38 });
	idle.PushBack({ 83,555,32,38 });
	idle.PushBack({ 81,631,32,38 });
	idle.speed = 0.2f;

	animation = &idle;

	collider = App->collision->AddCollider({ x,y,32,38 }, COLLIDER_TYPE::COLLIDER_ENEMY_RED, (Module*)App->enemies);
	position = iPoint(x, y);
	original_position = iPoint(x, y);
	EnemyLife = 2;
}

void Enemy_RedShip::Move()
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