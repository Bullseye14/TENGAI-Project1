#include "Application.h"
#include "Enemy_BrownCookie.h"
#include "ModuleCollision.h"

Enemy_BrownCookie::Enemy_BrownCookie(int x, int y) : Enemy(x, y)
{
	//fly.PushBack({ 5,72,21,22 });
	fly.PushBack({ 5,39,24,24 });
	fly.PushBack({ 38, 39, 24, 24 });
	fly.PushBack({ 71, 39, 24, 24 });
	fly.PushBack({ 104, 39, 24, 24 });
	fly.PushBack({ 137, 39, 24, 24 });
	fly.PushBack({ 170, 39, 24, 24 });
	fly.PushBack({ 203, 39, 24, 24 });
	fly.PushBack({ 236, 39, 24, 24 });
	fly.PushBack({ 5,72,24,24 });
	fly.PushBack({ 38, 72, 24, 24 });
	fly.PushBack({ 71, 72, 24, 24 });
	fly.PushBack({ 104, 72, 24, 24 });
	fly.PushBack({ 137, 72, 24, 24 });
	fly.PushBack({ 170, 72, 24, 24 });
	fly.PushBack({ 203, 72, 24, 24 });
	fly.PushBack({ 236, 72, 24, 24 });
	fly.speed = 0.2f;

	animation = &fly;

	collider = App->collision->AddCollider({ 0, 0, 24, 24 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_y = y;
}

void Enemy_BrownCookie::Move()
{
	if (going_up)
	{
		if (wave > 4.0f)
			going_up = false;
		else
			wave += 0.05f;
	}
	else
	{
		if (wave < 3.0f)
			going_up = true;
		else
			wave -= 0.05f;
	}

	position.y = int(float(original_y) + (25.0f * sinf(wave)));
	position.x -= 1;
}
