#include "Application.h"
#include "ModuleParticles.h"
#include "Enemy_BlueNinja.h"
#include "ModuleEnemies.h"
#include "ModuleCollision.h"
#include "ModuleInput.h"

Enemy_BlueNinja::Enemy_BlueNinja(int x, int y) : Enemy(x, y)
{
	/*path.PushBack({ 0.0f, 0.0f }, 30);
	path.PushBack({ 2.0f, 0.0f }, 30);
	path.PushBack({ 1.0f, 1.0f }, 40);
	path.PushBack({ 1.0f, -1.0f }, 40);
	path.PushBack({ 1.0f, 0.0f }, 25);*/

	fly.PushBack({ 206,567,26,35 });
	fly.speed = 0.19f;

	// floor animation 
	floor.PushBack({ 239,570,27,31 });
	floor.PushBack({ 239,570,27,31 });

	// run animation
	run.PushBack({ 277,568,24,33 });
	run.PushBack({ 209,611,24,33 });
	run.PushBack({ 241,611,33,35 });
	run.PushBack({ 281,609,33,32 });
	run.speed = 3.0f;

	animation = &run;


	collider = App->collision->AddCollider({ x,y,24,33 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	//App->collision->AddCollider({ x,y,66,37 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	//App->collision->AddCollider({ x,y,69,75 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	//collider = App->collision->AddCollider({ 0, 0, 24, 24 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_position = iPoint(x, y);
}

void Enemy_BlueNinja::Shoot() {
	App->particles->AddParticle(App->particles->Eshot, position.x - 10, position.y + animation->GetCurrentFrame().h / 2, COLLIDER_ENEMY_SHOT);
}

void Enemy_BlueNinja::Move()
{
	//if (current_time > last_time + 50) {
	if (App->input->keyboard[SDL_SCANCODE_2] == KEY_STATE::KEY_DOWN) {
		Shoot();
	}
	if (going_up)
	{
		if (wave > 4.0f) {
			going_up = false;
			Shoot();
		}
		else
			wave += 0.05f;
	}
	else
	{
		if (wave < 3.0f) {
			going_up = true;
			Shoot();
		}

		else
			wave -= 0.05f;
	}

	//position.y = int(float(original_y) + (25.0f * sinf(wave)));
	//position.x += 1;
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