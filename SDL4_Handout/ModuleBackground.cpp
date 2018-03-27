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
	ground.w = 758;
	ground.h = 11;
	

	// Background Tengai
	BG_forest.x = 0;
	BG_forest.y = 0;
	BG_forest.w = 759;
	BG_forest.h = 163;

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

	App->render->Blit(BG_forest_texture, 0, 0, &BG_forest, 0.75f);
	App->render->Blit(BG_forest_texture, 0, 222, &ground, 4.0f);
	

	return UPDATE_CONTINUE;
}