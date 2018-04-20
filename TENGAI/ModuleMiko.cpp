#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleMiko.h"
#include "ModuleAudio.h"

ModuleMiko::ModuleMiko()
{
	graphics = NULL;
	current_animation = NULL;

	path_spawn.PushBack({ 0.025f, 0.0f }, 100, &touch);

	path_die.PushBack({ 0.0f, 0.0f }, 2);
	path_die.PushBack({ -0.1f,-0.35f }, 5);
	path_die.PushBack({ -0.25f, 0.25f }, 15);
	path_die.PushBack({ -0.1f, 0.4f }, 40);
	
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

ModuleMiko::~ModuleMiko()
{}

// Load assets
bool ModuleMiko::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("tengai/spritesheet.png");
	MikosShot = App->audio->LoadFx("audio/MikosShot.wav");
	MikoCollision = App->audio->LoadFx("audio/MikoCollision.wav");

	position.x = 10;
	position.y = 50;
	alive = true;
	player_collider = App->collision->AddCollider({ position.x, position.y, 31, 31 },COLLIDER_TYPE::COLLIDER_PLAYER, this);

	return true;

}

// Unload assets
bool ModuleMiko::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);

	return true;
}



// Update: draw background
update_status ModuleMiko::Update()
{
	int camera_x = (-App->render->camera.x / 2);// Divided by camera.speed;

	if (alive) 
	{
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
			if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
			{
				if (!Shield_Animation)current_animation = &backward;
				if (position.x - speed > camera_x - 2)
				{
					position.x -= speed;
				}
			}
			if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
			{
				if (!Shield_Animation)current_animation = &idle;
				if (position.y > SCREEN_HEIGHT - 43) current_animation = &run;
									if (position.x + 29 + speed < SCREEN_WIDTH + camera_x)
				{
					position.x += speed;
				}
			}
			if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
			{
				if (!Shield_Animation)current_animation = &backward;
				if (position.y - speed > -2)
				{	
					position.y -= speed;		
				}
			}
			if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
			{
				if (!Shield_Animation)current_animation = &idle;
				if (position.y + 31 + speed < SCREEN_HEIGHT)
				{
					position.y += speed;
				}
			}
			if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
			{
				App->particles->AddParticle(App->particles->Mshot, position.x + 31, position.y + 6, COLLIDER_PLAYER_SHOT);
				Mix_PlayChannel(-1, MikosShot, 0);
			}
			if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE
				&& App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE
				&& App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE
				&& App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE
				&& !Shield_Animation)
			{
				if (position.y > SCREEN_HEIGHT-43) current_animation = &run;
				else current_animation = &idle;
			}
			// DEBUG INPUT
			if (App->input->keyboard[SDL_SCANCODE_F3] == KEY_STATE::KEY_REPEAT)
			{
				current_animation = &die;
				player_collider->to_delete = true;
				alive = false;
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
		else if (MikoLife != 3)
		{
			MikoLife++;
			Spawn();
		}
	}
	App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));
	return UPDATE_CONTINUE;

}

void ModuleMiko::Die() {
	path_die.Reset();
	alive = false;
	current_animation = &die;
	Mix_PlayChannel(-1, MikoCollision, 0);
	player_collider->to_delete = true;
}

bool ModuleMiko::Spawn() {
	//first time is called, spawn behind camera
	if (!Spawn_Animation)
	{
		path_spawn.Reset();
		current_animation = &touch;
		position = iPoint(-App->render->camera.x / 2, 50);
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

void ModuleMiko::OnCollision(Collider* c1, Collider* c2)
{
	Shield_Animation = (c1->type == COLLIDER_PLAYER && c2->type == COLLIDER_ENEMY) || (c2->type == COLLIDER_PLAYER && c1->type == COLLIDER_ENEMY);
	if (Shield_Animation)
	{
		if (power_ups > 0) { current_animation = &shield; }
		else if (alive) { Die(); }
	}

	if (c1->type == COLLIDER_PLAYER && c2->type == COLLIDER_ENEMY_SHOT) 
	{
		if (Mlife == 1) 
		{ 
			if (alive) 
			{
				Die();
				Mlife = 3;
			}			
		}
		else 
		{ 
			Mlife--; 
		}
	}
}