#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"

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
	
	idle.speed = 0.10f;

	// miko touched animation
	touch.PushBack({ 392, 10, 31, 27 });
	touch.PushBack({ 1,1,1,1 });
	touch.PushBack({ 432, 10, 31, 27 });
	touch.PushBack({ 1,1,1,1 });
	touch.PushBack({ 472, 10, 31, 27 });
	touch.speed = 0.1f;

	// backward animation (arcade sprite sheet)
	backward.PushBack({ 514,7,41,31 });
	backward.PushBack({ 555,7,31,31 });
	backward.PushBack({ 592,7,33,31 });
	backward.speed = 0.15f;

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
	die.PushBack({ 1,1,1,1 });
	die.PushBack({ 630,7,35,35 });
	die.PushBack({ 1,1,1,1 });
	die.PushBack({ 630,7,35,35 });
	die.PushBack({ 1,1,1,1 });
	die.PushBack({ 630,7,35,35 });
	die.PushBack({ 1,1,1,1 });
	die.PushBack({ 630,7,35,35 });
	die.PushBack({ 1,1,1,1 });
	die.loop = false;
	die.speed = 0.1f;

	// shield animation
	shield.PushBack({ 673,7,35,35 });
	shield.PushBack({ 713,7,35,35 });
	shield.PushBack({ 750,7,35,35 });
	shield.PushBack({ 795,7,35,35 });
	shield.PushBack({ 830,7,35,35 });
	shield.PushBack({ 870,7,35,35 });
	shield.PushBack({ 911,7,35,35 });
	shield.speed = 0.1f;
	
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
	alive = true;
	player_collider = App->collision->AddCollider({ position.x, position.y, 35, 31 }, COLLIDER_PLAYER, this);
	//bullet_collider = App->collision->AddCollider({ position.x + 31, position.y + 6,12,12 }, COLLIDER_PLAYER_SHOT);

	return true;

}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);

	return true;
}

void ModulePlayer::Touched() {
	current_animation = &touch;
}

void ModulePlayer::Die() {
	alive = false;
	current_animation = &die;
	MikoCollision = App->audio->LoadFx("audio/MikoCollision.wav");
	Mix_PlayChannel(-1, MikoCollision, 0);

	player_collider->to_delete = true;
	
}

// Update: draw background
update_status ModulePlayer::Update()
{
	int speed = 5;
	if (alive) {
		if (shield.Finished())
		{
			Shield_Animation = false;
			shield.Reset();
		}

		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
		{

			if (!Shield_Animation)current_animation = &backward;
			if (screen_position.x - speed > -10)
			{
				position.x -= speed;
				screen_position.x -= speed;
			}
		}
		else if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
		{
			if (!Shield_Animation)current_animation = &idle;
			if (screen_position.x + speed < SCREEN_WIDTH - current_animation->GetCurrentFrame().w)
			{
				position.x += speed;
				screen_position.x += speed;
			}

		}

		if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
		{
			if (!Shield_Animation)current_animation = &backward;
			if (screen_position.y - speed > -5)
			{
				position.y -= speed;
				screen_position.y -= speed;
			}
		}

		else if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
		{
			if (!Shield_Animation)current_animation = &idle;
			if (screen_position.y + speed < SCREEN_HEIGHT - current_animation->GetCurrentFrame().h)
			{
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
			&& App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE
			&& !Shield_Animation)
		{
			current_animation = &idle;
		}

		// DEBUG INPUT
		if (App->input->keyboard[SDL_SCANCODE_L] == KEY_STATE::KEY_REPEAT)
		{
			power_ups--;
		}
		if (App->input->keyboard[SDL_SCANCODE_H] == KEY_STATE::KEY_REPEAT)
		{
			power_ups++;
		}
		

		player_collider->SetPos(position.x, position.y);


	}
	// if dead
	else {
		
		current_animation = &die;
		//DEBUG INPUT
		/*if (App->input->keyboard[SDL_SCANCODE_1] == KEY_STATE::KEY_DOWN)
		{
			alive = true;
			player_collider = App->collision->AddCollider({ position.x, position.y, 35, 31 }, COLLIDER_PLAYER, this);
		}*/

	}

	App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));

	return UPDATE_CONTINUE;

}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{

	Shield_Animation = (c1->type == COLLIDER_PLAYER && c2->type == COLLIDER_ENEMY) || (c2->type == COLLIDER_PLAYER && c1->type == COLLIDER_ENEMY);
	if (Shield_Animation)
	{
		if (power_ups > 0) {
			current_animation = &shield;
		}
		else if (alive) {
			Die();
		}
	}

	Touch_Animation = (c1->type == COLLIDER_PLAYER && c2->type == COLLIDER_ENEMY_SHOT);
	if (Touch_Animation) 
	{
		Touched();
	}

	if (c1->type == COLLIDER_PLAYER && c2->type == COLLIDER_ENEMY_SHOT) 
	{
		if (Mlife == 1) 
		{ 
			if (alive) 
			{
				Die();
			}			
		}
		else 
		{ 
			Mlife--; 
		}
	}
	
}
