#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModulePlayerMotor.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer()
{
	position.x = 50;
	position.y = 40;

	//idle animation (arcade sprite sheet)
	idle.PushBack({ 389,7, 41,35 });
	idle.PushBack({ 430,7, 41,35 });
	idle.PushBack({ 471,7, 41,35 });
	idle.speed = 0.19f;

	// no forward animation (game)

	// backward animation (arcade sprite sheet)
	backward.PushBack({ 514,7,41,31 });
	backward.PushBack({ 555,7,31,31 });
	backward.PushBack({ 592,7,33,31 });
	backward.speed = 0.19f;

	// run animation (arcade sprite sheet)
	run.PushBack({  72,7,33,35 });
	run.PushBack({ 108,7,33,35 });
	run.PushBack({ 145,7,33,35 });
	run.PushBack({ 190,7,33,35 });
	run.PushBack({ 230,7,33,35 });
	run.PushBack({ 270,7,33,35 });
	run.PushBack({ 308,7,33,35 });
	run.PushBack({ 349,7,33,35 });
	run.speed = 0.19f;
	
	// die animation 
	die.PushBack({ 630,7,35,35 });

	// shield animation
	shield.PushBack({ 673,7,35,35 });
	shield.PushBack({ 713,7,35,35 });
	shield.PushBack({ 750,7,35,35 });
	shield.PushBack({ 795,7,35,35 });
	shield.PushBack({ 830,7,35,35 });
	shield.PushBack({ 870,7,35,35 });
	shield.PushBack({ 911,7,35,35 });
	shield.speed = 0.1f;

	// bullet animation
	bullet.PushBack({ 7,45,20,25 });
	
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	miko_texture = App->textures->Load("mikoSpritesheet.png"); // arcade version

	alive = true;
	speed = 1;
	current_animation = &idle;

	return ret;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	if (alive) {
		current_animation = &idle;
		if (App->input->keyboard[SDL_SCANCODE_RIGHT] == 1)
		{
			if (position.y >= 120) current_animation = &run;
			else current_animation = &idle;
			position.x += speed;
		}
		if (App->input->keyboard[SDL_SCANCODE_LEFT] == 1)
		{
			current_animation = &backward;
			position.x -= speed;
		}
		if (App->input->keyboard[SDL_SCANCODE_UP] == 1)
		{
			current_animation = &backward;
			position.y -= speed;
		}
		if (App->input->keyboard[SDL_SCANCODE_DOWN] == 1)
		{
			current_animation = &idle;
			position.y += speed;
		}
		if (App->input->keyboard[SDL_SCANCODE_R] == 1)
		{
			current_animation = &run;
		}
		
		if (App->input->keyboard[SDL_SCANCODE_S] == 1)
		{
			current_animation = &shield;
		}

		// Better if placed in a separated module with poll event and event key down, so firing is semiautomatic 
		if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
		{
			//Shoot();
		}
		
	}
	if (App->input->keyboard[SDL_SCANCODE_D] == 1)
		{
			current_animation = &die;
			alive = !alive;
		}
		

	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();
	
	
	App->render->Blit(miko_texture, position.x, position.y-r.h, &r);
	
	return UPDATE_CONTINUE;
}