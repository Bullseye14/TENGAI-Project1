#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleMiko.h"
#include "ModuleJunis.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneForest.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleSceneOutro.h"
#include "ModuleSceneRanking.h"
#include "ModuleFonts.h"


ModuleSceneRanking::ModuleSceneRanking() : Module() { }

ModuleSceneRanking::~ModuleSceneRanking() { }

bool ModuleSceneRanking::Start()
{
	LOG("Loading ranking scene");

	background_ranking = App->textures->Load("assets/tengai/WIN.png");

	AudioRanking = App->audio->LoadMusic("assets/audio/audiowin.ogg");
	Mix_PlayMusic(AudioRanking, 0);

	App->miko->won = false;
	App->junis->won = false;

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

	App->fonts->BlitText(30, 90, App->miko->font_score, App->miko->score_text);
	App->fonts->BlitText(30, 170, App->junis->font_score, App->junis->score_text);
	App->miko->score = 0;
	App->junis->score = 0;

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(App->scene_ranking, App->scene_intro, 1.0);
	}

	return UPDATE_CONTINUE;
}