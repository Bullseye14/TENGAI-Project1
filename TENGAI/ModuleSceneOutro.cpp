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

ModuleSceneOutro::ModuleSceneOutro() : Module() { }

ModuleSceneOutro::~ModuleSceneOutro() { }

bool ModuleSceneOutro::Init()
{
	LOG("Loading outro scene");

	background_outro = App->textures->Load("tengai/outro.png");

	audio_outro = App->audio->LoadMusic("audio/audiooutro.ogg");
	Mix_PlayMusic(audio_outro, -1);

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

	App->render->Blit(background_outro, 0, 0, NULL);

	if (App->input->keyboard[SDL_SCANCODE_RETURN] == 1)
	{
		App->fade->FadeToBlack(App->scene_outro, App->scene_intro, 1.0);
	}

	return UPDATE_CONTINUE;
}