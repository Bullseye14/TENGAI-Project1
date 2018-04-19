#include "Application.h"
#include "ModuleParticles.h"
#include "Enemy_BrownCookie.h"
#include "ModuleEnemies.h"
#include "ModuleCollision.h"
#include "ModuleInput.h"

Enemy_BrownCookie::Enemy_BrownCookie(int x, int y) : Enemy(x, y)
{
	path.PushBack({ 0.0f, 0.0f }, 30);
	path.PushBack({ 2.0f, 0.0f }, 30);
	path.PushBack({ 1.0f, 1.0f }, 40);
	path.PushBack({ 1.0f, -1.0f }, 40);
	path.PushBack({ 1.0f, 0.0f }, 25);

	idle.PushBack({ 43,44,91,107 });
	idle.PushBack({ 157,46,96,109 });
	idle.PushBack({ 253,49,93,107 });
	idle.PushBack({ 362,51,93,108 });
	idle.PushBack({ 38,167,91,108 });
	idle.PushBack({ 133,165,88,110 });
	idle.PushBack({ 240,173,98,101 });
	idle.PushBack({ 359,173,98,101 });
	idle.PushBack({ 6,289,97,102 });
	idle.PushBack({ 104,281,97,113 });
	idle.PushBack({ 202,277,97,121 });
	idle.PushBack({ 309,275,97,130 });
	idle.PushBack({ 412,307,98,133 });
	idle.PushBack({ 309,275,97,130 });
	idle.PushBack({ 202,277,97,121 });
	idle.PushBack({ 104,281,97,113 });
	idle.PushBack({ 6,289,97,102 });
	idle.PushBack({ 359,173,98,101 });
	idle.PushBack({ 240,173,98,101 });
	idle.PushBack({ 133,165,88,110 });
	idle.PushBack({ 38,167,91,108 });
	idle.PushBack({ 362,51,93,108 });
	idle.PushBack({ 253,49,93,107 });
	idle.PushBack({ 157,46,96,109 });
	idle.speed = 0.19f;

	// die animation 
	die.PushBack({ 43,44,91,107 });
	die.PushBack({ 1,1,1,1 });
	die.PushBack({ 43,44,91,107 });
	die.PushBack({ 1,1,1,1 });
	die.PushBack({ 43,44,91,107 });
	die.PushBack({ 1,1,1,1 });
	die.PushBack({ 43,44,91,107 });
	die.PushBack({ 1,1,1,1 });
	die.PushBack({ 43,44,91,107 });
	die.PushBack({ 1,1,1,1 });
	die.loop = false;
	die.speed = 0.1f;

	animation = &idle; 


	collider = App->collision->AddCollider({ x,y,100,150 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	//App->collision->AddCollider({ x,y,66,37 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	//App->collision->AddCollider({ x,y,69,75 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	//collider = App->collision->AddCollider({ 0, 0, 24, 24 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_position = iPoint(x,y);
}

void Enemy_BrownCookie::Shoot() {
	App->particles->AddParticle(App->particles->Eshot, position.x - 10, position.y+animation->GetCurrentFrame().h/2, COLLIDER_ENEMY_SHOT);
}

void Enemy_BrownCookie::Move()
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

/*void Enemy_BrownCookie::Die() {
	alive = false;
	current_animation = &die;

	collider->to_delete = true;

}

void Enemy_BrownCookie::OnCollision(Collider* c1, Collider* c2)
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

