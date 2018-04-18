#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleJunis.h"
#include "ModuleAudio.h"

ModuleJunis::ModuleJunis()
{
	graphics = NULL;
	current_animation = NULL;

	position.x = 0;
	position.y = 120;

	// idle animation
	idle.PushBack({ 4, 0, 27, 24 });
	idle.PushBack({ 46, 0, 27, 24 });
	idle.PushBack({ 89, 1, 27, 24 });
	idle.loop = true;
	idle.speed = 0.10f;

	// backward animation (arcade sprite sheet)
	backward.PushBack({ 79,33,16,28 });
	backward.speed = 0.15f;

	// run animation (arcade sprite sheet)
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
	die.PushBack({ 1,1,1,1 });
	die.PushBack({ 1,73,23,25 });
	die.PushBack({ 1,1,1,1 });
	die.PushBack({ 1,73,23,25 });
	die.PushBack({ 1,1,1,1 });
	die.PushBack({ 1,73,23,25 });
	die.PushBack({ 1,1,1,1 });
	die.PushBack({ 1,73,23,25 });
	die.PushBack({ 1,1,1,1 });
	die.loop = false;
	die.speed = 0.1f;

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

	graphics = App->textures->Load("tengai/junisSpritesheet.png");

	position.x = 10;
	position.y = 150;
	screen_position.x = 10;
	screen_position.y = 150;
	player_collider = App->collision->AddCollider({ position.x, position.y, 27, 28 }, COLLIDER_PLAYER, this);

	return true;

}

// Unload assets
bool ModuleJunis::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);

	return true;
}

void ModuleJunis::Die() {
	alive = false; 
	current_animation = &die;
	JunisCollision = App->audio->LoadFx("audio/JunisCollision.wav");
	Mix_PlayChannel(-1, JunisCollision, 0);

	player_collider->to_delete = true;
}

// Update: draw background
update_status ModuleJunis::Update()
{
	if (alive) {
		if (shield.Finished())
		{
			Shield_Animation = false;
			shield.Reset();
		}

		if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT)
		{

			if (!Shield_Animation)current_animation = &backward;
			if (screen_position.x - speed > -10)
			{
				position.x -= speed;
				screen_position.x -= speed;
			}
		}
		else if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT)
		{
			if (!Shield_Animation)current_animation = &idle;
			if (screen_position.x + speed < SCREEN_WIDTH - current_animation->GetCurrentFrame().w)
			{
				position.x += speed;
				screen_position.x += speed;
			}
		}

		if (App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT)
		{
			if (!Shield_Animation)current_animation = &backward;
			if (screen_position.y - speed > -5)
			{
				position.y -= speed;
				screen_position.y -= speed;
			}
		}

		else if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT)
		{
			if (!Shield_Animation)current_animation = &idle;
			if (screen_position.y + speed < SCREEN_HEIGHT - current_animation->GetCurrentFrame().h)
			{
				position.y += speed;
				screen_position.y += speed;
			}
		}

		if (App->input->keyboard[SDL_SCANCODE_RCTRL] == KEY_STATE::KEY_DOWN)
		{
			App->particles->AddParticle(App->particles->Sshot, position.x + 31, position.y + 6, COLLIDER_PLAYER_SHOT);
			JunisShot = App->audio->LoadFx("audio/JunisShot.wav");
			Mix_PlayChannel(-1, JunisShot, 0);
		}

		if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_IDLE
			&& App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_IDLE
			&& App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_IDLE
			&& App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_IDLE
			&& !Shield_Animation)
		{
			current_animation = &idle;
		}

		//Update collider position to player position
		player_collider->SetPos(position.x, position.y);
	}
	// if dead
	else {
		current_animation = &die;
		//DEBUG INPUT
		if (App->input->keyboard[SDL_SCANCODE_2] == KEY_STATE::KEY_DOWN)
		{
			alive = true;
			player_collider = App->collision->AddCollider({ position.x, position.y, 35, 31 }, COLLIDER_PLAYER, this);
		}

	}

	App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));

	return UPDATE_CONTINUE;	
}

void ModuleJunis::OnCollision(Collider* c1, Collider* c2)
{
	Shield_Animation = (c1->type == COLLIDER_PLAYER && c2->type == COLLIDER_ENEMY) || (c2->type == COLLIDER_PLAYER && c1->type == COLLIDER_ENEMY);
	if (Shield_Animation)
	{
		if (power_ups > 0) { current_animation = &shield; }
		else if (alive) { Die(); }
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