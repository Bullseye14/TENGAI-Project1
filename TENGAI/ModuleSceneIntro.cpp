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

ModuleSceneIntro::ModuleSceneIntro() : Module() { }

ModuleSceneIntro::~ModuleSceneIntro() { }

bool ModuleSceneIntro::Init() 
{ 
	LOG("Loading space scene");

	background = App->textures->Load("tengai/intro.png");

	intro = App->audio->LoadMusic("audio/audiointro.ogg");

	Mix_PlayMusic(intro, -1);

	//App->particles->AddParticle(App->particles->start, 160, 112);

	App->player->Enable();
	
	return true;
}

bool ModuleSceneIntro::CleanUp() 
{ 
	LOG("Unloading forest scene");

	App->textures->Unload(background);
	App->player->Disable();
	
	return true;
}

update_status ModuleSceneIntro::Update()
{
	App->render->camera.x = 3;

	App->render->Blit(background, 0, 0, NULL);

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(App->scene_intro, App->scene_forest, 1.0);
	}

	return UPDATE_CONTINUE;
}