#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModulePlayerMotor.h"


ModulePlayerMotor::ModulePlayerMotor()
{
	bullet.bullet.PushBack({  8,47,22,22 });
	bullet.bullet.PushBack({ 28,47,22,22 });
	bullet.bullet.PushBack({ 52,47,22,22 });
	bullet.bullet.PushBack({ 78,47,22,22 });
	bullet.bullet.PushBack({ 100,47,22,22 });
	//Animations
	//bullet.PushBack({ 125,47,22,22 });
	//bullet.PushBack({ 148,47,22,22 });
	//bullet.PushBack({ 170,47,22,22 });
	bullet.bullet.speed = 0.04f;
}


ModulePlayerMotor::~ModulePlayerMotor()
{
}
bool ModulePlayerMotor::Start()
{
	thisPlayer = App->player;
	graphics = thisPlayer->miko_texture;

	bullet.x = thisPlayer->position.getX();
	bullet.y = thisPlayer->position.getY();

	return true;
}

update_status ModulePlayerMotor::Update()
{
	SDL_Rect rect_Bullet = bullet.bullet.GetCurrentFrame();

	bool alive = thisPlayer->alive;
	if (bullet.x <= SCREEN_WIDTH) {

		bullet.x += 5;
		App->render->Blit(graphics,bullet.x,bullet.y,&rect_Bullet);
		//App->render->Blit(graphics, bullet.x-10, bullet.y, &rect_Bullet);
	}

	return UPDATE_CONTINUE;
}
void ModulePlayerMotor::Shoot()
{
}
