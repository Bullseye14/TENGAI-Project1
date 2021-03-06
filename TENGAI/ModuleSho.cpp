#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleSho.h"
#include "ModuleAudio.h"
#include "ModuleFonts.h"
#include "ModuleMiko.h"
#include "ModuleSceneForest.h"
#include <stdio.h>

ModuleSho::ModuleSho()
{
	graphics = NULL;
	current_animation = NULL;

	path_friend.PushBack({ 1.0f,0.0f }, 3, &friendApp);
	path_friend.PushBack({ 1.0f,0.0f }, 5000, &friendIdle);

	friendApp.PushBack({ 8,148,4,6 });
	friendApp.PushBack({ 16,148,5,6 });
	friendApp.PushBack({ 30,146,10,10 });
	friendApp.PushBack({ 49,146,11,12 });
	friendApp.loop = false;
	friendApp.speed = 0.1f;

	friendIdle.PushBack({ 121,174,15,13 });
	friendIdle.PushBack({ 146,174,15,13 });
	friendIdle.PushBack({ 170,174,14,13 });
	friendIdle.PushBack({ 193,173,15,13 });
	friendIdle.speed = 0.19f;

	path_spawn.PushBack({ 0.025f, 0.0f }, 100);

	path_die.PushBack({ 0.0f, 0.0f }, 2);
	path_die.PushBack({ -0.1f,-0.35f }, 5);
	path_die.PushBack({ -0.25f, 0.25f }, 15);
	path_die.PushBack({ -0.1f, 0.4f }, 40);

	path_win.PushBack({ 0.3f, 0.0f }, 7);
	path_win.PushBack({ 0.5f, 0.0f }, 15);
	path_win.PushBack({ 0.7f, 0.0f }, 40);
	
	// idle animation
	//idle.PushBack({ 181,8,22,27 });
	idle.PushBack({ 36, 8, 29, 27 });
	idle.PushBack({ 73, 9, 29, 26 });
	idle.PushBack({ 110, 9, 29, 27 });
	idle.speed = 0.10f;

	// touched animation now idle animation
	touch.PushBack({ 36, 8, 29, 27 });
	touch.PushBack({ 73, 9, 29, 26 });
	touch.PushBack({ 110, 9, 29, 27 });
	touch.speed = 0.10f;
	

	// backward animation (arcade sprite sheet)
	//backward.PushBack({ 181,8,22,27 });
	backward.PushBack({ 147,8,24,27 });
	backward.speed = 0.15f;

	// run animation (arcade sprite sheet)
	run.PushBack({ 8, 56, 29, 24 });
	run.PushBack({ 46, 57, 26, 23 });
	run.PushBack({ 79, 55, 27, 25 });
	run.PushBack({ 112, 57, 31, 24 });
	run.PushBack({ 149, 57, 30, 24 });
	run.PushBack({ 187, 58, 27, 23 });
	run.PushBack({ 221, 55, 30, 26 });
	run.PushBack({ 257, 54, 30, 26 });
	run.speed = 0.10f;

	// die animation now idle animation
	die.PushBack({ 36, 8, 29, 27 });;

	// shield animation now idle animation
	shield.PushBack({ 36, 8, 29, 27 });
	shield.PushBack({ 73, 9, 29, 26 });
	shield.PushBack({ 110, 9, 29, 27 });
	shield.speed = 0.10f;
	
}

ModuleSho::~ModuleSho()
{}

// Load assets
bool ModuleSho::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("assets/tengai/ShosSpritesheet.png");
	ShosShot = App->audio->LoadFx("assets/audio/MikosShot.wav");
	ShoCollision = App->audio->LoadFx("assets/audio/MikoCollision.wav");
	ShoPowerDown = App->audio->LoadFx("assets/audio/MikoPowerDown.wav");
	ShoPowerUp = App->audio->LoadFx("assets/audio/MikoPowerUp.wav");
	ShoFriendAttack = App->audio->LoadFx("assets/audio/MikoFriendAttack.wav");

	font_score = App->miko->font_score;
	font_players = App->miko->font_players;

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
	App->fonts->UnLoad(font_score);

	if (player_collider)
	{
		player_collider->to_delete = true;
	}
	if (bullet_collider)
	{
		bullet_collider->to_delete = true;
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
			if (Shield_Animation)
			{
				Shield_Animation = Shield();
			}
			if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT || SDL_GameControllerGetAxis(App->input->gamepad, SDL_CONTROLLER_AXIS_LEFTX) < 0)
			{
				if (!Shield_Animation)current_animation = &backward;
				if (position.x - speed > camera_x - 2)
				{
					position.x -= speed;
				}
			}
			if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT || SDL_GameControllerGetAxis(App->input->gamepad, SDL_CONTROLLER_AXIS_LEFTX) > 0)
			{
				if (!Shield_Animation) {
					current_animation = &idle;
					if (position.y > SCREEN_HEIGHT - 43 && App->scene_forest->enabled) current_animation = &run;
				}
				if (position.x + 29 + speed < SCREEN_WIDTH + camera_x)
				{
					position.x += speed;
				}
			}
			if (App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT || SDL_GameControllerGetAxis(App->input->gamepad, SDL_CONTROLLER_AXIS_LEFTY) < 0)
			{
				if (!Shield_Animation)current_animation = &backward;
				if (position.y - speed > -2 + camera_y)
				{	
					position.y -= speed;
				}
			}
			if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT || SDL_GameControllerGetAxis(App->input->gamepad, SDL_CONTROLLER_AXIS_LEFTY) > 0)
			{
				if (!Shield_Animation)current_animation = &idle;
				if (position.y + 31 + speed < SCREEN_HEIGHT + camera_y)
				{
					position.y += speed;
				}
			}
			if (App->input->keyboard[SDL_SCANCODE_RCTRL] == KEY_STATE::KEY_DOWN || SDL_GameControllerGetButton(App->input->gamepad, SDL_CONTROLLER_BUTTON_A) == 1)
			{
				App->particles->AddParticle(App->particles->Shoshot, position.x + 35, position.y + 6, COLLIDER_PLAYER_SHOT_P2);
				App->particles->AddParticle(App->particles->Shoshot, position.x + 10, position.y + 6, COLLIDER_PLAYER_SHOT_P2);
				Mix_PlayChannel(-1, ShosShot, 0);
			}
			if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_IDLE
				&& App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_IDLE
				&& App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_IDLE
				&& App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_IDLE
				&& SDL_GameControllerGetAxis(App->input->gamepad, SDL_CONTROLLER_AXIS_LEFTY) == 0
				&& SDL_GameControllerGetAxis(App->input->gamepad, SDL_CONTROLLER_AXIS_LEFTX) == 0
				&& !Shield_Animation)
			{
				if (position.y > SCREEN_HEIGHT-43 && App->scene_forest->enabled) current_animation = &run;
				else current_animation = &idle;
			}
			// DEBUG INPUT
			if (App->input->keyboard[SDL_SCANCODE_N] == KEY_STATE::KEY_REPEAT)
			{
				Die();
			}
		
		player_collider->SetPos(position.x, position.y);

	}
	else if (Spawn_Animation) {
		Spawn_Animation = Spawn();
		if (!Spawn_Animation) {
			alive = true;
		}
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
	score_x = camera_x + (SCREEN_SIZE*SCREEN_WIDTH * 2 / 3) -20;
	App->fonts->BlitText(score_x, 5 + camera_y, font_score, score_text);
	App->fonts->BlitText(score_x - 25, 5 + camera_y, font_players, "2");

	for (int i = 0; i < ShoLife; ++i) {
		App->particles->AddParticle(App->particles->Slife, (score_x + 65) + i * 18, camera_y + 2);
	}

	return UPDATE_CONTINUE;
}

void ModuleSho::Die() {
	if (ShoLife > 0)ShoLife--;
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

	if (App->input->keyboard[SDL_SCANCODE_RCTRL] == KEY_STATE::KEY_DOWN || SDL_GameControllerGetButton(App->input->gamepad, SDL_CONTROLLER_BUTTON_A) == 1)
	{
		App->particles->AddParticle(App->particles->Shosfriend, position.x + 9, position.y - 15, COLLIDER_PLAYER_SHOT_P2);
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
		position = iPoint(-App->render->camera.x-25, 80);
		player_collider = App->collision->AddCollider({ position.x, position.y, 31, 31 }, COLLIDER_TYPE::COLLIDER_PLAYER, this);
		Spawn_Animation = true;
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
		App->particles->AddParticle(App->particles->P_D, position.x + 5, position.y + 10, COLLIDER_TYPE::COLLIDER_NONE);
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
		if (power_ups < 5) {
			App->particles->AddParticle(App->particles->P_U, position.x + 5, position.y + 10, COLLIDER_TYPE::COLLIDER_NONE);
			power_ups++; }

		Mix_PlayChannel(-1, ShoPowerUp, 0);

		//TO CHANGE : PARTICLE POWER UP PROMPT (ModuleParticles.cpp);
		App->particles->AddParticle(App->particles->power_down, position.x + 5, position.y + 10, COLLIDER_TYPE::COLLIDER_NONE);
	}

	if (alive && (c1->type == COLLIDER_PLAYER && c2->type == COLLIDER_ENEMY_SHOT)) 
	{
		Die();
	}


}
