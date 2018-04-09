#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer()
{
	graphics = NULL;
	current_animation = NULL;

	position.x = 0;
	position.y = 120;

	offsetCamera = 3;

	// idle animation
	idle.PushBack({ 392, 10, 31, 27 });
	idle.PushBack({ 432, 10, 31, 27 });
	idle.PushBack({ 472, 10, 31, 27 });
	idle.loop = true;
	idle.speed = 0.19f;

	// backward animation (arcade sprite sheet)
	backward.PushBack({ 514,7,41,31 });
	backward.PushBack({ 555,7,31,31 });
	backward.PushBack({ 592,7,33,31 });
	backward.speed = 0.19f;

	// run animation (arcade sprite sheet)
	run.PushBack({ 72,7,33,35 });
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
	shield.speed = 0.15f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("tengai/spritesheet.png");

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	int speed = 2;
	

	if(App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
	{
		current_animation = &backward;
		position.x -= speed;
	}

	if(App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
	{
		current_animation = &idle;
		position.x += speed;
	}

	if(App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
	{
		current_animation = &idle;
		if (position.y + speed <= SCREEN_HEIGHT - 27) 
		{
			position.y += speed;
		}
	}

	if(App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
	{
		current_animation = &backward;

		if (position.y - speed >= 0) 
		{
			position.y -= speed;
		}
	}

	// TODO 3: Shoot lasers when the player hits SPACE

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN) 
	{
		App->particles->AddParticle(App->particles->Mshot, position.x + 31, position.y + 6);
	}

	if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE
		&& App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE
		&& App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE
		&& App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE) {

		current_animation = &idle;

		//if (position.x == )

	}

	// Draw everything --------------------------------------

	App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));

	return UPDATE_CONTINUE;
}