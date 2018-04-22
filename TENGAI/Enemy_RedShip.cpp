#include "Application.h"
#include "ModuleParticles.h"
#include "Enemy_RedShip.h"
#include "ModuleEnemies.h"
#include "ModuleCollision.h"
#include "ModuleInput.h"

Enemy_RedShip::Enemy_RedShip(int x, int y) : Enemy(x, y)
{
	path.PushBack({ -4.0f, 0.0f }, 15, &idle);
	path.PushBack({ -3.5f, 0.0f }, 15, &idle);
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
	path.PushBack({ 2.5f, 0.0f }, 10, &idle);
	path.PushBack({ 3.0f, 0.0f }, 10, &idle);
	path.PushBack({ 3.5f, 0.0f }, 10, &idle);
	path.PushBack({ 4.0f, 0.0f }, 1000, &idle);

	idle.PushBack({ 85,498,32,38 });
	idle.PushBack({ 83,578,32,38 });
	idle.PushBack({ 81,654,32,38 });
	idle.speed = 0.2f;

	animation = &idle;

	collider = App->collision->AddCollider({ x,y,32,38 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	position = iPoint(x, y);
	original_position = iPoint(x, y);
	EnemyLife = 2;
}

void Enemy_RedShip::Move()
{
	position = original_position + path.GetCurrentSpeed();
}