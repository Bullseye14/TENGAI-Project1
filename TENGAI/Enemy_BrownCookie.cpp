#include "Application.h"
#include "Enemy_BrownCookie.h"
#include "ModuleCollision.h"

Enemy_BrownCookie::Enemy_BrownCookie(int x, int y) : Enemy(x, y)
{

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
	idle.PushBack({ 408,271,98,133 });
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

	animation = &idle; 


	collider = App->collision->AddCollider({ x,y,100,150 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	//App->collision->AddCollider({ x,y,66,37 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	//App->collision->AddCollider({ x,y,69,75 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	//collider = App->collision->AddCollider({ 0, 0, 24, 24 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

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
void OnCollision(){

}
