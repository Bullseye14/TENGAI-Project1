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

ModuleSceneIntro::ModuleSceneIntro() : Module() { }

ModuleSceneIntro::~ModuleSceneIntro() { }

bool ModuleSceneIntro::Start() 
{ 
	LOG("Loading intro scene");

	background = App->textures->Load("assets/tengai/intro.png");
	//clouds = App->textures->Load("assets/tengai/waves_intro.png");

	intro = App->audio->LoadMusic("assets/audio/audiointro.ogg");
	Mix_PlayMusic(intro, -1);

	//App->particles->AddParticle(App->particles->start, 160, 112);
	
	return true;
}

bool ModuleSceneIntro::CleanUp() 
{ 
	LOG("Unloading intro scene");

	App->textures->Unload(background);
	
	return true;
}

update_status ModuleSceneIntro::Update()
{
	App->render->camera.x = 3;

	App->render->Blit(background, -2, 0, NULL);

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1 
		|| SDL_GameControllerGetButton(App->input->gamepad, SDL_CONTROLLER_BUTTON_A) == 1 
		|| SDL_GameControllerGetButton(App->input->gamepad2, SDL_CONTROLLER_BUTTON_A) == 1)
	{
		IntroFX = App->audio->LoadFx("assets/audio/intro_miko.wav");
		Mix_PlayChannel(-1, IntroFX, 0);
		App->fade->FadeToBlack(App->scene_intro, App->scene_forest, 1.0);
	}

	return UPDATE_CONTINUE;
}