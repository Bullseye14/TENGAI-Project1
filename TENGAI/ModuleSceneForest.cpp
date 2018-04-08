#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleSceneForest.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleSceneForest::ModuleSceneForest()
{
	// ground
	ground.x = 0;
	ground.y = 153;
	ground.w = 760;
	ground.h = 11;


	// Background Mid
	BG_mid.x = 0;
	BG_mid.y = 0;
	BG_mid.w = 760;
	BG_mid.h = 152;

	// background far
	BG_far.x = 0;
	BG_far.y = 0;
	BG_far.w = 760;
	BG_far.h = 40;
}

ModuleSceneForest::~ModuleSceneForest()
{}

// Load assets5
bool ModuleSceneForest::Start()
{
	LOG("Loading space scene");

	graphics = App->textures->Load("tengai/background.png");

	App->player->Enable();

	return true;
}

// UnLoad assets
bool ModuleSceneForest::CleanUp()
{
	LOG("Unloading space scene");

	App->textures->Unload(graphics);
	App->player->Disable();

	return true;
}

// Update: draw background
update_status ModuleSceneForest::Update()
{
	// Move camera forward -----------------------------
	int scroll_speed = 1;

	//Player auto scroll
	App->player->position.x += 1;

	App->render->camera.x -= 2;
	App->player->offsetCamera += 2;


	// Draw everything --------------------------------------
	//App->render->Blit(background, 0, 0, NULL);
	App->render->Blit(graphics, 0, 0, &BG_mid, 0.75f);
	App->render->Blit(graphics, 0, 0, &BG_far, 0.25f);
	App->render->Blit(graphics, 0, 152, &ground, 1.0f);

	return UPDATE_CONTINUE;
}