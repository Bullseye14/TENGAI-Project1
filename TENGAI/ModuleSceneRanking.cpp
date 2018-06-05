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
#include "ModuleFonts.h"
#include "ModuleSho.h"
#include <stdio.h>


ModuleSceneRanking::ModuleSceneRanking() : Module() { }

ModuleSceneRanking::~ModuleSceneRanking() { }

bool ModuleSceneRanking::Start()
{
	LOG("Loading ranking scene");

	App->miko->path_win.Reset();
	App->sho->path_win.Reset();

	background_ranking = App->textures->Load("assets/tengai/WIN.png");
	font = App->fonts->Load("assets/tengai/font1.png", "ABCDEFGHIJKLMNOPQRSTUVWXYZ(),-./0123456789-./0123456", 4);

	AudioRanking = App->audio->LoadMusic("assets/audio/audiowin.ogg");
	Mix_PlayMusic(AudioRanking, 0);

	App->miko->won = false;
	App->sho->won = false;

	return true;
}

bool ModuleSceneRanking::CleanUp()
{
	LOG("Unloading ranking scene");
	App->miko->score = 0;
	App->sho->score = 0;
	App->textures->Unload(background_ranking);
	App->fonts->UnLoad(font);
	//App->audio->UnloadMusic(AudioRanking);

	return true;
}

update_status ModuleSceneRanking::Update()
{
	App->render->camera.x = 3;
	App->render->Blit(background_ranking, -2, 0, NULL);
	//sprintf_s(App->miko->score_text, 10, "%7d", "ABCD");
	//perque siguin mes iguals tots, si no , jeje
	//App->fonts->BlitText(60, 30, font, "PLAYER 1");

	
	App->fonts->BlitText(40, 90, font, App->miko->score_text); // 
	App->fonts->BlitText(40, 170, font, App->sho->score_text);

	/*char sum_score[10];
	uint uint_sum_score = App->miko->score + App->sho->score;
	sprintf_s(sum_score, 10, "%7d", uint_sum_score);

	App->fonts->BlitText(200, SCREEN_HEIGHT/2, font, sum_score);*/
	

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1 
		|| SDL_GameControllerGetButton(App->input->gamepad, SDL_CONTROLLER_BUTTON_A) == 1
		|| SDL_GameControllerGetButton(App->input->gamepad2, SDL_CONTROLLER_BUTTON_A) == 1)
	{
		App->fade->FadeToBlack(App->scene_ranking, App->scene_intro, 1.0);
	}

	return UPDATE_CONTINUE;
}