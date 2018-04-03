#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "SDL/include/SDL_timer.h"
#include "ModulePlayerMotor.h"


/*		Les bales es disparen rectes, no roten, Animation => SDL_Rect
		Array of 50 bullets and cylcle to them, reach 50 => to bullet 0
		MEMORY LEAKS
*/
ModulePlayerMotor::ModulePlayerMotor()
{
	animation_bullet.PushBack({ 8,47,22,22 });
	animation_bullet.PushBack({ 28,47,22,22 });
	animation_bullet.PushBack({ 52,47,22,22 });
	animation_bullet.PushBack({ 78,47,22,22 });
	animation_bullet.PushBack({ 100,47,22,22 });
		
	//animation.PushBack({ 125,47,22,22 });
	//animation.PushBack({ 148,47,22,22 });
	//animation.PushBack({ 170,47,22,22 });
	animation_bullet.speed = 0.04f;
}


ModulePlayerMotor::~ModulePlayerMotor()
{
}

bool ModulePlayerMotor::Start()
{
	thisPlayer = App->player;
	graphics = thisPlayer->miko_texture;
	last_bullet_iterator = 0;

	return true;
}

update_status ModulePlayerMotor::Update()
{
	bool alive = thisPlayer->alive;
	currentTime = SDL_GetTicks();

	// last time + BULLET_TIME_OFFSET
 	if (currentTime > lastTime + 100 && App->input->keyboard[SDL_SCANCODE_SPACE] == 1) // && time_interval_between_shots
	{
		lastTime = currentTime;

		int x = thisPlayer->position.getX()+25;
		int y = thisPlayer->position.getY()-30;

 		magazineList[bullets_shot] = (Bullet(animation_bullet, x, y));
		/*if (bullets_shot >= 50) {
			bullets_shot = 0;
		}
		else*/ 
		++bullets_shot;
	}
	
	//for (std::list<Bullet>::iterator it = magazineList.begin(); it != magazineList.end();) {
	for (int i = bullets_shot; i > 0;--i) {

		if (magazineList[i].x <= SCREEN_WIDTH + thisPlayer->position.getX()) {
			magazineList[i].x = magazineList[i].x + 7; // + SPEED
			App->render->Blit(graphics, magazineList[i].x, magazineList[i].y, &(magazineList[i].animation).GetCurrentFrame());
			
		}
		else {
			if (bullets_shot > 0)
				bullets_shot--;
		}
	}
	
			
	return UPDATE_CONTINUE;
}
void ModulePlayerMotor::Shoot()
{
}
