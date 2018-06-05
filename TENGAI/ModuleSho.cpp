#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleSho.h"
#include "ModuleAudio.h"
#include "ModuleFonts.h"

#include <stdio.h>

ModuleSho::ModuleSho()
{
	graphics = NULL;
	current_animation = NULL;

	path_friend.PushBack({ 1.0f,0.0f }, 3, &friendApp);
	path_friend.PushBack({ 1.0f,0.0f }, 5000, &friendIdle);

	friendApp.PushBack({ 24,86,3,5 });
	friendApp.PushBack({ 58,85,11,6 });
	friendApp.PushBack({ 96,83,17,10 });
	friendApp.PushBack({ 133,83,20,11 });
	friendApp.loop = false;
	friendApp.speed = 0.1f;

	friendIdle.PushBack({ 171,81,24,14 });
	friendIdle.PushBack({ 211,82,24,13 });
	friendIdle.PushBack({ 251,82,24,13 });
	friendIdle.PushBack({ 292,82,23,13 });
	friendIdle.speed = 0.19f;

	path_spawn.PushBack({ 0.025f, 0.0f }, 100, &touch);

	path_die.PushBack({ 0.0f, 0.0f }, 2);
	path_die.PushBack({ -0.1f,-0.35f }, 5);
	path_die.PushBack({ -0.25f, 0.25f }, 15);
	path_die.PushBack({ -0.1f, 0.4f }, 40);

	path_win.PushBack({ 0.3f, 0.0f }, 7);
	path_win.PushBack({ 0.5f, 0.0f }, 15);
	path_win.PushBack({ 0.7f, 0.0f }, 40);
	
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
	touch.PushBack({ 1,1,1,1 });
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

ModuleSho::~ModuleSho()
{}

// Load assets
bool ModuleSho::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("assets/tengai/spritesheet.png");
	ShosShot = App->audio->LoadFx("assets/audio/MikosShot.wav");
	ShoCollision = App->audio->LoadFx("assets/audio/MikoCollision.wav");
	ShoPowerDown = App->audio->LoadFx("assets/audio/MikoPowerDown.wav");
	ShoPowerUp = App->audio->LoadFx("assets/audio/MikoPowerUp.wav");
	ShoFriendAttack = App->audio->LoadFx("assets/audio/MikoFriendAttack.wav");

	font_score = App->fonts->Load("assets/tengai/fonts3.png", "0123456789", 1);
	font_players = App->fonts->Load("assets/tengai/p1p2.png", "12", 1);// 1 = P1: , 2 = P2:

	position.x = 10;
	position.y = 80;
	alive = true;
	player_collider = App->collision->AddCollider({ position.x, position.y, 31, 31 },COLLIDER_TYPE::COLLIDER_PLAYER, this);

	return true;

}

// Unload assets
bool ModuleSho::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);
	App->fonts->UnLoad(font_players);
	if (player_collider)
	{
		player_collider->to_delete = true;
	}
	return true;
}



// Update: draw background
update_status ModuleSho::Update()
{
	int camera_x = -App->render->camera.x;// Divided by camera.speed;
	int camera_y = -App->render->camera.y;

	if (alive) 
	{
		if (Spawn_Animation) {
			Spawn_Animation = Spawn();
		}
		else 
		{	
			if (Shield_Animation)
			{
				Shield_Animation = Shield();
			}
			if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT || SDL_GameControllerGetAxis(App->input->gamepad, SDL_CONTROLLER_AXIS_LEFTX) < 0)
			{
				if (!Shield_Animation)current_animation = &backward;
				if (position.x - speed > camera_x - 2)
				{
					position.x -= speed;
				}
			}
			if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT || SDL_GameControllerGetAxis(App->input->gamepad, SDL_CONTROLLER_AXIS_LEFTX) > 0)
			{
				if (!Shield_Animation) {
					current_animation = &idle;
					if (position.y > SCREEN_HEIGHT - 43) current_animation = &run;
				}
				if (position.x + 29 + speed < SCREEN_WIDTH + camera_x)
				{
					position.x += speed;
				}
			}
			if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT || SDL_GameControllerGetAxis(App->input->gamepad, SDL_CONTROLLER_AXIS_LEFTY) < 0)
			{
				if (!Shield_Animation)current_animation = &backward;
				if (position.y - speed > -2 + camera_y)
				{	
					position.y -= speed;
				}
			}
			if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT || SDL_GameControllerGetAxis(App->input->gamepad, SDL_CONTROLLER_AXIS_LEFTY) > 0)
			{
				if (!Shield_Animation)current_animation = &idle;
				if (position.y + 31 + speed < SCREEN_HEIGHT + camera_y)
				{
					position.y += speed;
				}
			}
			if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN || SDL_GameControllerGetButton(App->input->gamepad, SDL_CONTROLLER_BUTTON_A) == 1)
			{
				App->particles->AddParticle(App->particles->Mshot, position.x + 35, position.y + 6, COLLIDER_PLAYER_SHOT_P1);
				App->particles->AddParticle(App->particles->Mshot, position.x + 10, position.y + 6, COLLIDER_PLAYER_SHOT_P1);
				Mix_PlayChannel(-1, ShosShot, 0);
			}
			if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE
				&& App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE
				&& App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE
				&& App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE
				&& SDL_GameControllerGetAxis(App->input->gamepad, SDL_CONTROLLER_AXIS_LEFTY) == 0
				&& SDL_GameControllerGetAxis(App->input->gamepad, SDL_CONTROLLER_AXIS_LEFTX) == 0
				&& !Shield_Animation)
			{
				if (position.y > SCREEN_HEIGHT-43) current_animation = &run;
				else current_animation = &idle;
			}
			// DEBUG INPUT
			if (App->input->keyboard[SDL_SCANCODE_M] == KEY_STATE::KEY_REPEAT)
			{
				Die();
			}
		}
		player_collider->SetPos(position.x, position.y);
	}
	// if dead 
	else {
		if (!path_die.loop) 
		{
			position += path_die.GetCurrentSpeed();
		}
		else if (ShoLife > 0)
		{
			Spawn();
		}
	}

	if (power_ups > 1) { Friend(); }

	App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));

	sprintf_s(score_text, 10, "%7d", score);
	score_x = camera_x + 30;
	App->fonts->BlitText(score_x, 5, font_score, score_text);
	App->fonts->BlitText(score_x - 25, 5, font_players, "1");

	return UPDATE_CONTINUE;
}

void ModuleSho::Die() {
	if (ShoLife>0)ShoLife--;
	power_ups = 1;
	path_die.Reset();
	alive = false;
	current_animation = &die;
	Mix_PlayChannel(-1, ShoCollision, 0);
	player_collider->to_delete = true;
}

void ModuleSho::Friend() 
{
	shofr = iPoint(position.x - 15, position.y - 15);
	
	path_friend.GetCurrentSpeed(&Shofriend);

	App->render->Blit(graphics, position.x - 12, position.y - 12, &(Shofriend->GetCurrentFrame()));

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN || SDL_GameControllerGetButton(App->input->gamepad, SDL_CONTROLLER_BUTTON_A) == 1)
	{
		App->particles->AddParticle(App->particles->BasaroShot, position.x + 9, position.y - 15, COLLIDER_PLAYER_SHOT_P1);
		Mix_PlayChannel(-1, ShoFriendAttack, 0);
	}
}

void ModuleSho::Win()
{
	power_ups = 1;
	position += path_win.GetCurrentSpeed();
	current_animation = &idle;
	player_collider->to_delete = true;
	//path_win.accumulated_speed = fPoint(0.0f, 0.0f);
}

bool ModuleSho::Spawn() {
	//first time is called, spawn behind camera
	if (!Spawn_Animation)
	{
		path_spawn.Reset();
		current_animation = &touch;
		position = iPoint(-App->render->camera.x-25, 50);
		player_collider = App->collision->AddCollider({ position.x, position.y, 31, 31 }, COLLIDER_TYPE::COLLIDER_PLAYER, this);
		Spawn_Animation = true;
		alive = true;
	}
	//Actually moving behind the camera
	else {
		position += path_spawn.GetCurrentSpeed();
	}
	//if is finished
	return !path_spawn.loop;
}

bool ModuleSho::Shield() {
	if (!Shield_Animation)
	{
		if (power_ups >= 2) {
		power_ups--;	
		Mix_PlayChannel(-1, ShoPowerDown, 0);
		//TO CHANGE : PARTICLE POWER DOWN  PROMPT(ModuleParticles.cpp);
		App->particles->AddParticle(App->particles->power_down, position.x + 5, position.y + 10, COLLIDER_TYPE::COLLIDER_NONE);
		}
		shield.Reset();
		current_animation = &shield;
		Shield_Animation = true;
	}
	return !shield.Finished();
}

void ModuleSho::OnCollision(Collider* c1, Collider* c2)
{
	if (c1->type == COLLIDER_PLAYER && c2->type == COLLIDER_ENEMY || c1->type == COLLIDER_PLAYER && c2->type == COLLIDER_ENEMY_GREEN || c1->type == COLLIDER_PLAYER && c2->type == COLLIDER_ENEMY_RED || c1->type == COLLIDER_PLAYER && c2->type == COLLIDER_ENEMY_BOSS)
	{
		Shield();
	}
	if (c1->type == COLLIDER_PLAYER && c2->type == COLLIDER_POWER_UP) {
		if (power_ups < 5) { power_ups++; }

		Mix_PlayChannel(-1, ShoPowerUp, 0);

		//TO CHANGE : PARTICLE POWER UP PROMPT (ModuleParticles.cpp);
		App->particles->AddParticle(App->particles->power_down, position.x + 5, position.y + 10, COLLIDER_TYPE::COLLIDER_NONE);
	}

	if (c1->type == COLLIDER_PLAYER && c2->type == COLLIDER_ENEMY_SHOT) 
	{
		Die();
	}


}
