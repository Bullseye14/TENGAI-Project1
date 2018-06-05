#include "Application.h"
#include "ModuleParticles.h"
#include "Enemy_Samurai.h"
#include "ModuleEnemies.h"
#include "ModuleCollision.h"
#include "ModuleInput.h"
#include "ModuleRender.h"

Enemy_Samurai::Enemy_Samurai(int x, int y) : Enemy(x, y)
{
	path2.PushBack({ 0.0f,0.0f }, 5000, &idle);

	path.PushBack({ -2.0f, 0.0f }, 70, &idle);
	path.PushBack({ 2.0f, -1.5f }, 150, &idle);
	path.PushBack({ 2.0f, 0.0f }, 40, &attack);
	path.PushBack({ 2.0f, 0.0f }, 1, &attacking);
	path.PushBack({ 2.0f, 0.0f }, 40, &attack);
	path.PushBack({ 2.0f, 0.0f }, 1, &attacking);
	path.PushBack({ 2.0f, 0.0f }, 40, &attack);
	path.PushBack({ 2.0f, 0.0f }, 1, &attacking);
	path.PushBack({ 2.0f, 0.0f }, 40, &attack);
	path.PushBack({ 2.0f, 0.0f }, 1, &attacking);
	path.PushBack({ 2.0f, 0.0f }, 40, &attack);
	path.PushBack({ 2.0f, 0.0f }, 1, &attacking);
	path.PushBack({ 2.0f, 1.5f }, 1000, &idle);
	

	/*wave.PushBack({ 9,1088,33,11 });
	wave.PushBack({ 59,1075,47,26 });
	wave.PushBack({ 131,1058,46,41 });
	wave.PushBack({ 202,1022,44,77 });
	wave.PushBack({ 264,1027,45,72 });
	wave.PushBack({ 333,1030,45,69 });
	wave.PushBack({ 395,1049,47,44 });
	wave.loop = false;
	wave.speed = 0.2f;*/
	
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
	attack.speed = 0.05f;

	attacking.PushBack({ 279,898,43,55 });
	
	animation = &wave;

	collider = App->collision->AddCollider({ x,y,32,38 }, COLLIDER_TYPE::COLLIDER_ENEMY_RED, (Module*)App->enemies);
	position = iPoint(x, y);
	original_position = iPoint(x, y);
	EnemyLife = 2;
}

void Enemy_Samurai::Shoot() 
{
	App->particles->AddParticle(App->particles->Eshot1, position.x, position.y + animation->GetCurrentFrame().h / 2, COLLIDER_ENEMY_SHOT);
	App->particles->AddParticle(App->particles->Eshot6, position.x, position.y + animation->GetCurrentFrame().h / 2, COLLIDER_ENEMY_SHOT);
	App->particles->AddParticle(App->particles->Eshot8, position.x, position.y + animation->GetCurrentFrame().h / 2, COLLIDER_ENEMY_SHOT);
}

void Enemy_Samurai::Move()
{

	if (this->animation == &attacking) { Shoot(); }
	
	if (screen == 1 && position.x <= -App->render->camera.x / 2)
	{
		position = original_position + path2.GetCurrentSpeed(&animation);
	}
	else
	{
		screen = 0;
		position = original_position + path.GetCurrentSpeed(&animation);
	}
	
}