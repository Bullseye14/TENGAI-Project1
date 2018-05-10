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


ModuleSceneOutro::ModuleSceneOutro() : Module() { }

ModuleSceneOutro::~ModuleSceneOutro() { }

bool ModuleSceneOutro::Start()
{
	LOG("Loading outro scene");

	background_outro = App->textures->Load("assets/tengai/outro.png");

	AudioOutro = App->audio->LoadMusic("assets/audio/audiooutro.ogg");
	Mix_PlayMusic(AudioOutro, -1);

	return true;
}

bool ModuleSceneOutro::CleanUp()
{
	LOG("Unloading outro scene");

	App->textures->Unload(background_outro);

	return true;
}

update_status ModuleSceneOutro::Update()
{
	App->render->camera.x = 3;

	App->render->Blit(background_outro, -2, 0, NULL);

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_REPEAT 
		|| SDL_GameControllerGetButton(App->input->gamepad, SDL_CONTROLLER_BUTTON_A) == 1
		|| SDL_GameControllerGetButton(App->input->gamepad2, SDL_CONTROLLER_BUTTON_A) == 1)
	{
		App->fade->FadeToBlack(App->scene_outro, App->scene_intro, 1.0);
	}

	return UPDATE_CONTINUE;
}