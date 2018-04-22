#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleJunis.h"
#include "ModuleAudio.h"
#include "ModuleFonts.h"
#include "ModuleMiko.h"

#include <stdio.h>

ModuleJunis::ModuleJunis()
{
	graphics = NULL;
	current_animation = NULL;

	path_socrates.PushBack({ 1.0f,0.0f }, 3, &SocratesApp);
	path_socrates.PushBack({ 1.0f,0.0f }, 5000, &SocratesIdle);

	SocratesApp.PushBack({ 144,35,5,3 });
	SocratesApp.PushBack({ 175,33,11,6 });
	SocratesApp.PushBack({ 210,33,19,8 });
	SocratesApp.PushBack({ 256,32,22,9 });
	SocratesApp.loop = false;
	SocratesApp.speed = 0.1f;

	SocratesIdle.PushBack({ 299,50,26,13 });
	SocratesIdle.PushBack({ 334,50,29,13 });
	SocratesIdle.PushBack({ 373,53,30,12 });
	SocratesIdle.PushBack({ 417,52,29,12 });
	SocratesIdle.speed = 0.19f;

	path_spawn.PushBack({ 0.025f, 0.0f }, 100, &touch);

	path_die.PushBack({ 0.0f, 0.0f }, 2);
	path_die.PushBack({ -0.1f,-0.35f }, 5);
	path_die.PushBack({ -0.25f, 0.25f }, 15);
	path_die.PushBack({ -0.1f, 0.4f }, 40);

	path_win.PushBack({ 0.3f, 0.0f }, 7);
	path_win.PushBack({ 0.5f, 0.0f }, 15);
	path_win.PushBack({ 0.7f, 0.0f }, 40);

	// idle animation
	idle.PushBack({ 4, 0, 27, 24 });
	idle.PushBack({ 46, 0, 27, 24 });
	idle.PushBack({ 89, 1, 27, 24 });
	idle.speed = 0.10f;

	// junis touched animation
	touch.PushBack({ 4, 0, 27, 24 });
	touch.PushBack({ 1,1,1,1 });
	touch.PushBack({ 46, 0, 27, 24 });
	touch.PushBack({ 1,1,1,1 });
	touch.PushBack({ 89, 1, 27, 24 });
	touch.PushBack({ 1,1,1,1 });
	touch.speed = 0.1f;

	// backward animation (arcade sprite sheet)
	backward.PushBack({ 79,33,16,28 });
	backward.speed = 0.15f;

	// run animation (arcade sprite sheet)
	run.PushBack({ 4, 0, 27, 24 });
	run.PushBack({ 46, 0, 27, 24 });
	run.PushBack({ 89, 1, 27, 24 });
	run.speed = 0.10f;
	/*run.PushBack({ 72,7,33,35 });
	run.PushBack({ 108,7,33,35 });
	run.PushBack({ 145,7,33,35 });
	run.PushBack({ 190,7,33,35 });
	run.PushBack({ 230,7,33,35 });
	run.PushBack({ 270,7,33,35 });
	run.PushBack({ 308,7,33,35 });
	run.PushBack({ 349,7,33,35 });
	run.speed = 0.19f;*/

	// die animation 
	die.PushBack({ 1,73,23,25 });

	// shield animation
	shield.PushBack({ 37,111,19,26 });
	shield.PushBack({ 71,112,14,24 });
	shield.PushBack({ 102,110,19,26 });
	shield.PushBack({ 5,110,15,26 });
	shield.PushBack({ 37,111,19,26 });
	shield.speed = 0.1f;

}

ModuleJunis::~ModuleJunis()
{}

// Load assets
bool ModuleJunis::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("assets/tengai/junisSpritesheet.png");
	graphics2 = App->textures->Load("assets/tengai/ParticlesSpritesheet.png");
	JunisShot = App->audio->LoadFx("assets/audio/JunisShot.wav");
	JunisCollision = App->audio->LoadFx("assets/audio/JunisCollision.wav");
	JunisPowerDown = App->audio->LoadFx("assets/audio/JunisPowerDown.wav");
	JunisPowerUp = App->audio->LoadFx("assets/audio/JunisPowerUp.wav");
	SocratesAttack = App->audio->LoadFx("assets/audio/JunisFriendAttack.wav");

	font_score = App->fonts->Load("assets/tengai/fonts3.png", "0123456789", 1);
	font_players = App->fonts->Load("assets/tengai/p1p2.png", "12", 1);

	position.x = 10;
	position.y = 150;
	alive = true;
	player_collider = App->collision->AddCollider({ position.x, position.y, 27, 28 }, COLLIDER_PLAYER, this);

	return true;

}

// Unload assets
bool ModuleJunis::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);
	App->fonts->UnLoad(font_score);
	if (player_collider)
		player_collider->to_delete = true;

	return true;
}

// Update: draw background
update_status ModuleJunis::Update()
{
	int camera_x = (-App->render->camera.x / 2);// Divided by camera.speed;

	if (alive) {
		if (shield.Finished())
		{
			Shield_Animation = false;
			shield.Reset();
		}
		else if (Spawn_Animation) {
			Spawn_Animation = Spawn();
		}
		else
		{
			if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT)
			{
				if (!Shield_Animation)current_animation = &backward;
				if (position.x - speed > camera_x - 2)
				{
					position.x -= speed;
				}
			}
			else if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT)
			{
				if (!Shield_Animation)current_animation = &idle;
				if (position.y > SCREEN_HEIGHT - 43) current_animation = &run;
				if (position.x + 29 + speed < SCREEN_WIDTH + camera_x)
				{
					position.x += speed;
				}
			}
			if (App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT)
			{
				if (!Shield_Animation)current_animation = &backward;
				if (position.y - speed > -2)
				{
					position.y -= speed;
				}
			}
			else if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT)
			{
				if (!Shield_Animation)current_animation = &idle;
				if (position.y + 31 + speed < SCREEN_HEIGHT)
				{
					position.y += speed;
				}
			}
			if (App->input->keyboard[SDL_SCANCODE_RCTRL] == KEY_STATE::KEY_DOWN)
			{
				App->particles->AddParticle(App->particles->Jshot, position.x + 31, position.y + 6, COLLIDER_PLAYER_SHOT_P2);
				Mix_PlayChannel(-1, JunisShot, 0);
			}
			if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_IDLE
				&& App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_IDLE
				&& App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_IDLE
				&& App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_IDLE
				&& !Shield_Animation)
			{
				if (position.y > SCREEN_HEIGHT - 43) current_animation = &run;
				else current_animation = &idle;
			}
			if (App->input->keyboard[SDL_SCANCODE_F3] == KEY_STATE::KEY_DOWN)
			{
				JunisLife = 3;
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
		else if (JunisLife != 3)
		{
			JunisLife++;
			Spawn();
		}
	}

	if (position.x == 2500) { won = true; App->miko->won = true; }

	if (power_ups >= 2) { Friend(); }
	if (App->input->keyboard[SDL_SCANCODE_H] == KEY_STATE::KEY_DOWN) { Friend(); }

	App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));

	sprintf_s(score_text, 10, "%7d", score);
	score_x = camera_x + (SCREEN_WIDTH) * 2 / 3;

	App->fonts->BlitText(score_x, 5, font_score, score_text);
	App->fonts->BlitText(score_x - 25, 5, font_players, "2");// 1 = P1: , 2 = P2:
	

	return UPDATE_CONTINUE;	
}

void ModuleJunis::Die() {
	path_die.Reset();
	alive = false;
	current_animation = &die;
	Mix_PlayChannel(-1, JunisCollision, 0);
	player_collider->to_delete = true;
}

void ModuleJunis::Win() 
{
	position += path_win.GetCurrentSpeed();
	current_animation = &idle;
	player_collider->to_delete = true;
}

void ModuleJunis::Friend() 
{
	socrates_pos = iPoint(position.x - 15, position.y - 15);

	path_socrates.GetCurrentSpeed(&AnimSocrates);

	App->render->Blit(graphics, position.x - 12, position.y - 12, &(AnimSocrates->GetCurrentFrame()));

	if (App->input->keyboard[SDL_SCANCODE_RCTRL] == KEY_STATE::KEY_DOWN)
	{
		App->particles->AddParticle(App->particles->SocratesShot1, position.x + 9, position.y - 15, COLLIDER_PLAYER_SHOT_P2);
		App->particles->AddParticle(App->particles->SocratesShot2, position.x + 9, position.y - 15, COLLIDER_PLAYER_SHOT_P2);
		Mix_PlayChannel(-1, SocratesAttack, 0);
	}
}

bool ModuleJunis::Spawn() {
	//first time is called, spawn behind camera
	if (!Spawn_Animation)
	{
		path_spawn.Reset();
		current_animation = &touch;
		position = iPoint(-App->render->camera.x / 2, 150);
		player_collider = App->collision->AddCollider({ position.x, position.y, 27, 28 }, COLLIDER_PLAYER, this);
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

void ModuleJunis::OnCollision(Collider* c1, Collider* c2)
{
	Shield_Animation = (c1->type == COLLIDER_PLAYER && c2->type == COLLIDER_ENEMY) || (c2->type == COLLIDER_PLAYER && c1->type == COLLIDER_ENEMY);
	if (Shield_Animation)
	{
		if (power_ups > 1) { power_ups--; }
		Mix_PlayChannel(-1, JunisPowerDown, 0);
		if (power_ups > 0) { current_animation = &shield; }
		else if (alive) { Die(); }
	}
	if (c1->type == COLLIDER_PLAYER && c2->type == COLLIDER_POWER_UP) {
		power_ups++;
		Mix_PlayChannel(-1, JunisPowerUp, 0);

		//TO CHANGE : PARTICLE POWER UP PROMPT (ModuleParticles.cpp);
		App->particles->AddParticle(App->particles->power_down, position.x + 5, position.y + 10, COLLIDER_TYPE::COLLIDER_NONE);
	}

	if (c1->type == COLLIDER_PLAYER && c2->type == COLLIDER_ENEMY_SHOT)
	{
		if (Jlife == 1)
		{
			if (alive)
			{
				Die();
				Jlife = 3;
			}
		}
		else
		{
			Jlife--;
		}
	}
}