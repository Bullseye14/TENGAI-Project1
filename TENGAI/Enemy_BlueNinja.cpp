#include "Application.h"
#include "ModuleParticles.h"
#include "Enemy_BlueNinja.h"
#include "ModuleEnemies.h"
#include "ModuleCollision.h"
#include "ModuleInput.h"

Enemy_BlueNinja::Enemy_BlueNinja(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 206,567,26,35 });

	// run animation
	run.PushBack({ 239,570,27,31 });
	run.PushBack({ 239,570,27,31 });
	run.PushBack({ 277,568,24,33 });
	run.PushBack({ 209,611,24,33 });
	run.PushBack({ 241,611,33,35 });
	run.PushBack({ 281,609,33,32 });
	run.speed = 0.2f;

	path.PushBack({ 0.0f, 2.0f }, 93, &fly);
	path.PushBack({ -2.0f, 0.0f }, 30, &run);
	path.PushBack({ 4.0f, -4.0f }, 100, &fly);

	animation = &fly;

	collider = App->collision->AddCollider({ x,y,24,33 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_position = iPoint(x, y);
	EnemyLife = 2;
}

void Enemy_BlueNinja::Shoot() {
	App->particles->AddParticle(App->particles->blueShot, position.x, position.y + animation->GetCurrentFrame().h / 2, COLLIDER_ENEMY_SHOT);
}

void Enemy_BlueNinja::Move()
{
	position = original_position + path.GetCurrentSpeed(&animation);
 
	if (position.x == SCREEN_WIDTH - 100) { Shoot(); }
}