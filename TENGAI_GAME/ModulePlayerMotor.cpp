#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "SDL/include/SDL_timer.h"
#include "ModulePlayerMotor.h"


/*		Les bales es disparen rectes, no roten, Animation => SDL_Rect
		PLAYER CAN'T MOVE, 
	
		
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

	return true;
}

update_status ModulePlayerMotor::Update()
{
	bool alive = thisPlayer->alive;
	currentTime = SDL_GetTicks();

 	if (currentTime > lastTime + 100 && App->input->keyboard[SDL_SCANCODE_SPACE] == 1) // && time_interval_between_shots
	{
		lastTime = currentTime;

		int x = thisPlayer->position.getX()+25;
		int y = thisPlayer->position.getY()-30;
 		magazineList.push_back(Bullet(animation_bullet, x, y));
	}
	for (std::list<Bullet>::iterator it = magazineList.begin(); it != magazineList.end();) {

		if (it->x <= SCREEN_WIDTH + thisPlayer->position.getX()) {
			it->x = it->x + 7;
			App->render->Blit(graphics, it->x, it->y, &(it->animation).GetCurrentFrame());
			++it;
		}
		else {
			it = magazineList.erase(it);
		}
	}
	
			
	return UPDATE_CONTINUE;
}
void ModulePlayerMotor::Shoot()
{
}