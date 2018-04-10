#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneForest.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleSceneOutro.h"
#include "ModuleCollision.h"
#include "ModuleEnemy.h"

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
	LOG("Loading forest scene");

	graphics = App->textures->Load("tengai/background.png");

	SceneForest = App->audio->LoadMusic("audio/audioforest.ogg");
	Mix_PlayMusic(SceneForest, -1);

	App->player->Enable();
	App->collision->Enable();
	App->enemy->Enable();

	return true;
}

// UnLoad assets
bool ModuleSceneForest::CleanUp()
{
	LOG("Unloading forest scene");

	App->textures->Unload(graphics);
	App->player->Disable();
	App->collision->Disable();
	App->enemy->Disable();

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

	if (App->input->keyboard[SDL_SCANCODE_RETURN] == 1)
	{
		App->fade->FadeToBlack(App->scene_forest, App->scene_outro, 1.0);
	}

	return UPDATE_CONTINUE;
}