#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleBullet.h"



ModuleBullet::ModuleBullet(Animation animation, int x, int y)
{
	this->graphics = App->player->miko_texture;
	this->animation = animation;
	this->x = x;
	this->y = y;
	
}


ModuleBullet::ModuleBullet()
{
	//this->graphics = App->player->miko_texture;
}

ModuleBullet::~ModuleBullet()
{
}


bool ModuleBullet::Start()
{
	return true;
}

update_status ModuleBullet::Update()
{
	
	if (this->x <= SCREEN_WIDTH) {
		//SDL_Rect rect_Bullet = this->animation.GetCurrentFrame();
		//
	}
	return UPDATE_CONTINUE;
}
