#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer()
{
	graphics = NULL;
	current_animation = NULL;

	position.x = 0;
	position.y = 120;

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

	position.x = 10;
	position.y = 60;
	screen_position.x = 10;
	screen_position.y = 60;

	distance_backward = position.x;
	distance_forward = SCREEN_WIDTH * SCREEN_SIZE - position.x;

	distance_up = position.y;
	distance_down = SCREEN_HEIGHT - position.y;

	player_collider = App->collision->AddCollider({ position.x, position.y, 35, 31 }, COLLIDER_PLAYER,this);

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
	int speed = 5;
	

	if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
	{

		current_animation = &backward;
		if (screen_position.x - speed > -10) {
			position.x -= speed;
			screen_position.x -= speed;
		}
	}
	//MUST HAVE ELSE
	else if(App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
	{
		current_animation = &idle;
		if (screen_position.x + speed < SCREEN_WIDTH - current_animation->GetCurrentFrame().w) {
				position.x += speed;
				screen_position.x += speed;
		}	
		
	}

	if(App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
	{
		current_animation = &backward;
		if (screen_position.y - speed > 0) {
				position.y -= speed;
				screen_position.y -= speed;
			}		
	}

    if(App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
	{
		current_animation = &idle;
		if (screen_position.y + speed < SCREEN_HEIGHT - current_animation->GetCurrentFrame().h) {
			position.y += speed;
			screen_position.y += speed;
		}
		
	}

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN) 
	{
		App->particles->AddParticle(App->particles->Mshot, position.x + 31, position.y + 6, COLLIDER_PLAYER_SHOT);
		MikosShot = App->audio->LoadFx("audio/MikosShot.wav");
		Mix_PlayChannel(-1, MikosShot, 0);
	}

	if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE
		&& App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE
		&& App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE
		&& App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE) 
	{
		current_animation = &idle;	
	}
	if (Shield_Animation == true) {
		current_animation = &shield;
	}
	else if (Shield_Animation == false) {
		App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));
	}
	
	//Update collider position to player position

	player_collider->SetPos(position.x, position.y);


	// Draw everything --------------------------------------

	App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));

	return UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	
	//SHA DE CANVIAR PER COLLIDER_WALL SI MANTENIM AQUEST MODE 
	//DE DETECTAR QUE ESTAR DINS LA PANTALLA, ESTA AMB COLLIDER_ENEMY 
	//FOR TESTING PURPOSES
	if (c1->type == COLLIDER_ENEMY || c2->type == COLLIDER_ENEMY) {
		Shield_Animation = true;
	}
	else {
		Shield_Animation = false;
	}
}
