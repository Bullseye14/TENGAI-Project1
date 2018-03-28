#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleBackground.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleBackground::ModuleBackground()
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

	//700x525

}

ModuleBackground::~ModuleBackground()
{}

// Load assets
bool ModuleBackground::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	BG_forest_texture = App->textures->Load("background.png");
	return ret;
}

// Update: draw background
update_status ModuleBackground::Update()
{
	// Draw everything --------------------------------------

	App->render->Blit(BG_forest_texture, 0, 0, &BG_mid, 0.75f);
	App->render->Blit(BG_forest_texture, 0, 0, &BG_far, 0.25f);
	App->render->Blit(BG_forest_texture, 0, 152, &ground, 1.0f);
	

	return UPDATE_CONTINUE;
}