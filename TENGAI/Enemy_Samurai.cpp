#include "Application.h"
#include "ModuleParticles.h"
#include "Enemy_Samurai.h"
#include "ModuleEnemies.h"
#include "ModuleCollision.h"
#include "ModuleInput.h"
#include "ModuleRender.h"

Enemy_Samurai::Enemy_Samurai(int x, int y) : Enemy(x, y)
{
	wave.PushBack({ 9,1088,33,11 });
	wave.PushBack({ 59,1075,47,26 });
	wave.PushBack({ 131,1058,46,41 });
	wave.PushBack({ 202,1022,44,77 });
	wave.PushBack({ 264,1027,45,72 });
	wave.PushBack({ 333,1030,45,69 });
	wave.PushBack({ 395,1049,47,44 });
	wave.loop = false;
	wave.speed = 0.2f;
	
	idle.PushBack({ 8,903,41,34 });
	idle.PushBack({ 59,903,41,50 });
	idle.PushBack({ 112,903,41,61 });
	idle.PushBack({ 169,903,40,57 });
	idle.PushBack({ 225,905,38,54 });
	idle.loop = false;
	idle.speed = 0.2f;

	attack.PushBack({ 401,903,34,51 });
	attack.PushBack({ 344,903,34,47 });
	attack.PushBack({ 8,980,35,43 });
	attack.PushBack({ 59,980,35,44 });
	attack.PushBack({ 121,980,45,43 });
	attack.PushBack({ 279,898,43,55 });
	attack.speed = 0.2f;

	animation = &wave;

	path.PushBack({ 1.0f, 0.0f }, 200, &idle);

	collider = App->collision->AddCollider({ x,y,32,38 }, COLLIDER_TYPE::COLLIDER_ENEMY_RED, (Module*)App->enemies);
	position = iPoint(x, y);
	original_position = iPoint(x, y);
	EnemyLife = 2;
}

void Enemy_Samurai::Move()
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