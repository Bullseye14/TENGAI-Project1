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
	LOG("Loading intro scene");

	outro = App->textures->Load("tengai/outro.png");

	audiooutro = App->audio->LoadMusic("audio/audiooutro.ogg");
	Mix_PlayMusic(audiooutro, -1);

	App->player->Enable();

	return true;
}

bool ModuleSceneOutro::CleanUp()
{
	LOG("Unloading outro scene");

	App->textures->Unload(outro);
	App->player->Disable();

	return true;
}

update_status ModuleSceneOutro::Update()
{
	App->render->camera.x = 3;

	App->render->Blit(outro, 0, 0, NULL);

	return UPDATE_CONTINUE;
}