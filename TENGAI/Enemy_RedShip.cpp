#include "Application.h"
#include "ModuleParticles.h"
#include "Enemy_RedShip.h"
#include "ModuleEnemies.h"
#include "ModuleCollision.h"
#include "ModuleInput.h"

Enemy_RedShip::Enemy_RedShip(int x, int y) : Enemy(x, y)
{
	path.PushBack({ 0.0f, 0.0f }, 500);

	idle.PushBack({ 85,498,32,38 });
	idle.PushBack({ 83,578,32,38 });
	idle.PushBack({ 81,654,32,38 });
	idle.speed = 0.19f;

	// die animation 
	die.PushBack({ 85,498,32,38 });
	die.PushBack({ 1,1,1,1 });
	die.PushBack({ 83,578,32,38 });
	die.PushBack({ 1,1,1,1 });
	die.PushBack({ 81,654,32,38 });
	die.PushBack({ 1,1,1,1 });
	die.loop = false;
	die.speed = 0.1f;

	animation = &idle;

	collider = App->collision->AddCollider({ x,y,32,38 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_position = iPoint(x, y);
	EnemyLife = 2;
}

void Enemy_RedShip::Move()
{
	position = original_position + path.GetCurrentSpeed();
}