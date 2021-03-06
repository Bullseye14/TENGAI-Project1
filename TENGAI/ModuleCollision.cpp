#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleSceneForest.h"
#include "ModuleMiko.h"
#include "ModuleParticles.h"
#include "ModuleSho.h"

ModuleCollision::ModuleCollision()
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER_SHOT_P1] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER_SHOT_P2] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY_SHOT] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_POWER_UP] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY_BOSS] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY_GREEN] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY_RED] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_SAMURAI] = true;

	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER_SHOT_P1] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER_SHOT_P2] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_POWER_UP] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY_BOSS] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY_GREEN] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY_RED] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_SAMURAI] = false;

	matrix[COLLIDER_PLAYER_SHOT_P1][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER_SHOT_P1][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER_SHOT_P1][COLLIDER_PLAYER_SHOT_P1] = false;
	matrix[COLLIDER_PLAYER_SHOT_P1][COLLIDER_PLAYER_SHOT_P2] = false;
	matrix[COLLIDER_PLAYER_SHOT_P1][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_PLAYER_SHOT_P1][COLLIDER_POWER_UP] = false;
	matrix[COLLIDER_PLAYER_SHOT_P1][COLLIDER_ENEMY_BOSS] = true;
	matrix[COLLIDER_PLAYER_SHOT_P1][COLLIDER_ENEMY_GREEN] = true;
	matrix[COLLIDER_PLAYER_SHOT_P1][COLLIDER_ENEMY_RED] = true;
	matrix[COLLIDER_PLAYER_SHOT_P1][COLLIDER_SAMURAI] = true;

	matrix[COLLIDER_PLAYER_SHOT_P2][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER_SHOT_P2][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER_SHOT_P2][COLLIDER_PLAYER_SHOT_P2] = false;
	matrix[COLLIDER_PLAYER_SHOT_P2][COLLIDER_PLAYER_SHOT_P1] = false;
	matrix[COLLIDER_PLAYER_SHOT_P2][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_PLAYER_SHOT_P2][COLLIDER_POWER_UP] = false;
	matrix[COLLIDER_PLAYER_SHOT_P2][COLLIDER_ENEMY_BOSS] = true;
	matrix[COLLIDER_PLAYER_SHOT_P2][COLLIDER_ENEMY_GREEN] = true;
	matrix[COLLIDER_PLAYER_SHOT_P2][COLLIDER_ENEMY_RED] = true;
	matrix[COLLIDER_PLAYER_SHOT_P2][COLLIDER_SAMURAI] = true;

	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER_SHOT_P1] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER_SHOT_P2] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_POWER_UP] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ENEMY_BOSS] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ENEMY_GREEN] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ENEMY_RED] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_SAMURAI] = false;

	matrix[COLLIDER_POWER_UP][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_POWER_UP][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_POWER_UP][COLLIDER_PLAYER_SHOT_P1] = false;
	matrix[COLLIDER_POWER_UP][COLLIDER_PLAYER_SHOT_P2] = false;
	matrix[COLLIDER_POWER_UP][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_POWER_UP][COLLIDER_POWER_UP] = false;
	matrix[COLLIDER_POWER_UP][COLLIDER_ENEMY_BOSS] = false;
	matrix[COLLIDER_POWER_UP][COLLIDER_ENEMY_GREEN] = false;
	matrix[COLLIDER_POWER_UP][COLLIDER_ENEMY_RED] = false;
	matrix[COLLIDER_POWER_UP][COLLIDER_SAMURAI] = false;

	matrix[COLLIDER_ENEMY_RED][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY_RED][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_ENEMY_RED][COLLIDER_PLAYER_SHOT_P1] = true;
	matrix[COLLIDER_ENEMY_RED][COLLIDER_PLAYER_SHOT_P2] = true;
	matrix[COLLIDER_ENEMY_RED][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_ENEMY_RED][COLLIDER_POWER_UP] = false;
	matrix[COLLIDER_ENEMY_RED][COLLIDER_ENEMY_BOSS] = false;
	matrix[COLLIDER_ENEMY_RED][COLLIDER_ENEMY_GREEN] = false;
	matrix[COLLIDER_ENEMY_RED][COLLIDER_ENEMY_RED] = false;
	matrix[COLLIDER_ENEMY_RED][COLLIDER_SAMURAI] = false;

	matrix[COLLIDER_ENEMY_BOSS][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY_BOSS][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_ENEMY_BOSS][COLLIDER_PLAYER_SHOT_P1] = true;
	matrix[COLLIDER_ENEMY_BOSS][COLLIDER_PLAYER_SHOT_P2] = true;
	matrix[COLLIDER_ENEMY_BOSS][COLLIDER_POWER_UP] = false;
	matrix[COLLIDER_ENEMY_BOSS][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_ENEMY_BOSS][COLLIDER_ENEMY_RED] = false;
	matrix[COLLIDER_ENEMY_BOSS][COLLIDER_ENEMY_GREEN] = false;
	matrix[COLLIDER_ENEMY_BOSS][COLLIDER_ENEMY_BOSS] = false;
	matrix[COLLIDER_ENEMY_BOSS][COLLIDER_SAMURAI] = false;

	matrix[COLLIDER_ENEMY_GREEN][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY_GREEN][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_ENEMY_GREEN][COLLIDER_PLAYER_SHOT_P1] = true;
	matrix[COLLIDER_ENEMY_GREEN][COLLIDER_PLAYER_SHOT_P2] = true;
	matrix[COLLIDER_ENEMY_GREEN][COLLIDER_POWER_UP] = false;
	matrix[COLLIDER_ENEMY_GREEN][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_ENEMY_GREEN][COLLIDER_ENEMY_RED] = false;
	matrix[COLLIDER_ENEMY_GREEN][COLLIDER_ENEMY_BOSS] = false;
	matrix[COLLIDER_ENEMY_GREEN][COLLIDER_ENEMY_GREEN] = false;
	matrix[COLLIDER_ENEMY_GREEN][COLLIDER_SAMURAI] = false;
	matrix[COLLIDER_SAMURAI][COLLIDER_SAMURAI] = false;
	
}

// Destructor
ModuleCollision::~ModuleCollision()
{}

update_status ModuleCollision::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr && colliders[i]->to_delete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	// Calculate collisions
	Collider* c1;
	Collider* c2;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// skip empty colliders
		if (colliders[i] == nullptr)
			continue;

		c1 = colliders[i];

		// avoid checking collisions already checked
		for (uint k = i + 1; k < MAX_COLLIDERS; ++k)
		{
			// skip empty colliders
			if (colliders[k] == nullptr)
				continue;

			c2 = colliders[k];

			if (c1->CheckCollision(c2->rect) == true)
			{
				if (matrix[c1->type][c2->type] && c1->callback)
					c1->callback->OnCollision(c1, c2);

				if (matrix[c2->type][c1->type] && c2->callback)
					c2->callback->OnCollision(c2, c1);
			}
		}
	}

	return UPDATE_CONTINUE;
}
bool ModuleCollision::Start() {
	debug = false;
	return true;
}

// Called before render is available
update_status ModuleCollision::Update()
{

	DebugDraw();

	return UPDATE_CONTINUE;
}

void ModuleCollision::DebugDraw()
{
	if (App->input->keyboard[SDL_SCANCODE_F1] == KEY_DOWN)
		debug = !debug;

	if (debug == false)
		return;


	// God Mode
	if (App->input->keyboard[SDL_SCANCODE_F5] == KEY_DOWN)
	{
		if (!f5) {
			App->miko->player_collider->to_delete = true;
			App->sho->player_collider->to_delete = true;
			f5 = true;
		}
		else {
			App->miko->player_collider = App->collision->AddCollider({ App->miko->position.x, App->miko->position.y, 31, 31 }, COLLIDER_PLAYER, this);
			App->sho->player_collider = App->collision->AddCollider({ App->sho->position.x, App->sho->position.y, 27, 28 }, COLLIDER_PLAYER, this);
			f5 = false;

		}
	}

	Uint8 alpha = 80;
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
			continue;

		switch (colliders[i]->type)
		{
		case COLLIDER_NONE: // white
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
			break;
		case COLLIDER_PLAYER: // green
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
			break;
		case COLLIDER_ENEMY: // red
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
			break;
		case COLLIDER_ENEMY_BOSS: // red
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
			break;
		case COLLIDER_ENEMY_GREEN: // red
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
			break;
		case COLLIDER_ENEMY_RED: // red
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
			break;
		case COLLIDER_PLAYER_SHOT_P1: // yellow
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
			break;
		case COLLIDER_PLAYER_SHOT_P2: // pink
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 255, alpha);
			break;
		case COLLIDER_ENEMY_SHOT: // magenta
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha);
			break;
		}
	}
}

// Called before quitting
bool ModuleCollision::CleanUp()
{
	LOG("Freeing all colliders");

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* ModuleCollision::AddCollider(SDL_Rect rect, COLLIDER_TYPE type, Module* callback)
{
	Collider* ret = nullptr;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, callback);
			break;
		}
	}

	return ret;
}


bool Collider::CheckCollision(const SDL_Rect& r) const
{

	if ((r.x > rect.x + rect.w) || (r.y > rect.y + rect.h)) { return false; }

	if ((rect.x > r.x + r.w) || (rect.y > r.y + r.h)) { return false; }

	return true;
}