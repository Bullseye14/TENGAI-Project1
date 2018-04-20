#include "Application.h"
#include "ModuleParticles.h"
#include "Enemy_BlueNinja.h"
#include "ModuleEnemies.h"
#include "ModuleCollision.h"
#include "ModuleInput.h"

Enemy_BlueNinja::Enemy_BlueNinja(int x, int y) : Enemy(x, y)
{
	//path.PushBack({ 0.0f, 0.0f }, 300);
	path.PushBack({ 0.0f, 2.0f }, 93);
	path.PushBack({ -2.0f, 0.0f }, 30);
	path.PushBack({ 4.0f, -4.0f }, 100);
	path.loop = false;

	fly.PushBack({ 206,567,26,35 });
	fly.speed = 0.19f;

	// run animation
	floor.PushBack({ 239,570,27,31 });
	floor.PushBack({ 239,570,27,31 });
	run.PushBack({ 277,568,24,33 });
	run.PushBack({ 209,611,24,33 });
	run.PushBack({ 241,611,33,35 });
	run.PushBack({ 281,609,33,32 });
	run.speed = 3.0f;

	animation = &fly;

	collider = App->collision->AddCollider({ x,y,24,33 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_position = iPoint(x, y);
	
}

void Enemy_BlueNinja::Shoot() {
	App->particles->AddParticle(App->particles->Eshot1, position.x - 10, position.y + animation->GetCurrentFrame().h / 2, COLLIDER_ENEMY_SHOT);
}

void Enemy_BlueNinja::Move()
{
	if (running) 
	{ 
		air = false;
		animation = &run;
	}
	else 
	{
		air = true;
		running = false;
		animation = &fly;
	}

	position = original_position + path.GetCurrentSpeed();	
}

/*void Enemy_BlueNinja::Die() {
alive = false;
current_animation = &die;

collider->to_delete = true;

}

void Enemy_BlueNinja::OnCollision(Collider* c1, Collider* c2)
{
//App->particles->AddParticle(App->particles->explosion, position.x, position.y);
if (c1->type == COLLIDER_ENEMY && c2->type == COLLIDER_PLAYER_SHOT)
{
if (Elife == 1)
{
if (alive)
{
Die();
}
}
else
{
Elife--;
}
}
}*/