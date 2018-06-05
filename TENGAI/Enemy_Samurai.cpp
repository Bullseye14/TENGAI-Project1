#include "Application.h"
#include "ModuleParticles.h"
#include "Enemy_Samurai.h"
#include "ModuleEnemies.h"
#include "ModuleCollision.h"
#include "ModuleInput.h"
#include "ModuleRender.h"

Enemy_Samurai::Enemy_Samurai(int x, int y) : Enemy(x, y)
{
	wave.PushBack({ 10,366,33,11 });
	wave.PushBack({ 60,353,47,26 });
	wave.PushBack({ 132,336,46,41 });
	wave.PushBack({ 203,300,44,77 });
	wave.PushBack({ 265,305,45,72 });
	wave.PushBack({ 334,308,45,69 });
	wave.PushBack({ 396,327,47,44 });
	wave.loop = false;
	wave.speed = 0.2f;
	
	idle.PushBack({ 9,181,41,34 });
	idle.PushBack({ 60,181,41,50 });
	idle.PushBack({ 113,181,41,61 });
	idle.PushBack({ 170,181,40,57 });
	idle.PushBack({ 226,183,38,54 });
	idle.speed = 0.2f;

	animation = &wave;

	collider = App->collision->AddCollider({ x,y,32,38 }, COLLIDER_TYPE::COLLIDER_ENEMY_RED, (Module*)App->enemies);
	position = iPoint(x, y);
	original_position = iPoint(x, y);
	EnemyLife = 2;
}

void Enemy_Samurai::Move()
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