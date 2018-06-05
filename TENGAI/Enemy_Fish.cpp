#include "Application.h"
#include "ModuleParticles.h"
#include "Enemy_Fish.h"
#include "ModuleEnemies.h"
#include "ModuleCollision.h"
#include "ModuleInput.h"
#include "ModuleRender.h"

Enemy_Fish::Enemy_Fish(int x, int y) : Enemy(x, y)
{
	path2.PushBack({ 0.0f,0.0f }, 5000, &idle);

	path.PushBack({ 0.0f, 0.0f }, 40, &idle);
	path.PushBack({ 1.0f, 0.0f }, 20, &idle);
	path.PushBack({ 1.0f, 0.0f }, 1, &attack);
	path.PushBack({ 1.0f, 0.0f }, 20, &idle);
	path.PushBack({ 1.0f, 0.0f }, 1, &attack);
	path.PushBack({ 1.0f, 0.0f }, 20, &idle);
	path.PushBack({ 1.0f, 0.0f }, 1, &attack);
	path.PushBack({ 0.0f, 0.2f }, 5000, &idle);

	idle.PushBack({ 33,821,29,23 });
	idle.PushBack({ 84,821,30,23 });
	idle.PushBack({ 132,821,31,23 });
	idle.speed = 0.2f;
	
	attack.PushBack({ 185,821,31,23 });

	path.PushBack({ 1.0f, 0.0f }, 200, &idle);

	animation = &idle;

	collider = App->collision->AddCollider({ x,y,32,38 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	position = iPoint(x, y);
	original_position = iPoint(x, y);
	EnemyLife = 2;
}

void Enemy_Fish::Shoot() 
{
	App->particles->AddParticle(App->particles->Eshot1, position.x, position.y + animation->GetCurrentFrame().h / 2, COLLIDER_ENEMY_SHOT);
}

void Enemy_Fish::Move()
{
	if (this->animation == &attack) { Shoot(); }

	if (position.x <= -App->render->camera.x / 2)
	{
		position = original_position + path2.GetCurrentSpeed(&animation);
	}
	else if (position.x <= -App->render->camera.x + SCREEN_WIDTH)
	{
		position = original_position + path.GetCurrentSpeed(&animation);
	}
	
}