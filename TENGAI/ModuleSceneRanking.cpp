#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleMiko.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneForest.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleSceneOutro.h"
#include "ModuleSceneRanking.h"


ModuleSceneRanking::ModuleSceneRanking() : Module() { }

ModuleSceneRanking::~ModuleSceneRanking() { }

bool ModuleSceneRanking::Start()
{
	LOG("Loading ranking scene");

	background_ranking = App->textures->Load("tengai/WIN.png");

	AudioRanking = App->audio->LoadMusic("audio/audiooutro.ogg");
	Mix_PlayMusic(AudioRanking, -1);

	return true;
}

bool ModuleSceneRanking::CleanUp()
{
	LOG("Unloading ranking scene");

	App->textures->Unload(background_ranking);

	return true;
}

update_status ModuleSceneRanking::Update()
{
	App->render->camera.x = 3;

	App->render->Blit(background_ranking, -2, 0, NULL);

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(App->scene_ranking, App->scene_forest, 1.0);
	}

	return UPDATE_CONTINUE;
}