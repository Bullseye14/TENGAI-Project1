#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleBackground.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleBackground::ModuleBackground()
{
	// ground
	ground.x = 8;
	ground.y = 391;
	ground.w = 896;
	ground.h = 72;

	// Background / sky
	background.x = 72;
	background.y = 208;
	background.w = 768;
	background.h = 176;

	// Background Tengai
	background_T.x = 0;
	background_T.y = 0;
	background_T.w = 759;
	background_T.h = 163;

	// Ship
	ship.x = 8;
	ship.y = 24;
	ship.w = 530;
	ship.h = 190;

	// flag animation
	flag.PushBack({848, 208, 40, 40});
	flag.PushBack({848, 256, 40, 40});
	flag.PushBack({848, 304, 40, 40});
	flag.speed = 0.08f;

	// girl animation
	girl.PushBack({ 624,16,32,56 });
	girl.PushBack({ 624,80,32,56 });
	girl.PushBack({ 624,144,32,56 });
	girl.speed = 0.08f;

	// two men animation
	twomen.PushBack({ 552,16,64,56 });
	twomen.PushBack({ 552,80,64,56 });
	twomen.PushBack({ 552,144,64,56 });
	twomen.speed = 0.08f;

	// green man animation
	greenAN.PushBack({ 664,16,32,56 });
	greenAN.PushBack({ 664,80,32,56 });
	greenAN.speed = 0.08f;

	//blue man animation
	blueAN.PushBack({ 704,16,48,56 });
	blueAN.PushBack({ 704,80,48,56 });
	blueAN.PushBack({ 704,144,48,56 });
	blueAN.speed = 0.08f;

	// brown man animation
	brownAN.PushBack({ 760,16,40,40 });
	brownAN.PushBack({ 760,64,40,40 });
	brownAN.PushBack({ 760,112,40,40 });
	brownAN.speed = 0.08f;

	// purple man animation
	purpleAN.PushBack({ 808,24,48,32 });
	purpleAN.PushBack({ 808,72,48,32 });
	purpleAN.PushBack({ 808,120,48,32 });
	purpleAN.speed = 0.08f;

}

ModuleBackground::~ModuleBackground()
{}

// Load assets
bool ModuleBackground::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	graphics = App->textures->Load("ken_stage.png");
	background_TENGAI = App->textures->Load("background.png");

	return ret;
}

// Update: draw background
update_status ModuleBackground::Update()
{
	// Draw everything --------------------------------------
	//App->render->Blit(graphics, 0, 0, &background, 0.75f); // sea and sky
	App->render->Blit(background_TENGAI, 0, 0, &background_T, 0.75f);
	App->render->Blit(graphics, 560, 8, &(flag.GetCurrentFrame()), 0.75f); // flag animation

	// TODO 2: Draw the ship from the sprite sheet with some parallax effect

	App->render->Blit(graphics, 0, 0, &ship, 0.7f);

	// TODO 3: Animate the girl on the ship (see the sprite sheet)

	App->render->Blit(graphics, 192, 104, &(girl.GetCurrentFrame()), 0.7f);
	App->render->Blit(graphics, 128, 104, &(twomen.GetCurrentFrame()), 0.7f);
	App->render->Blit(graphics, 288, 96, &(blueAN.GetCurrentFrame()), 0.7f);
	App->render->Blit(graphics, 224, 104, &(greenAN.GetCurrentFrame()), 0.7f);
	App->render->Blit(graphics, 128, 24, &(purpleAN.GetCurrentFrame()), 0.7f);
	App->render->Blit(graphics, 88, 24, &(brownAN.GetCurrentFrame()), 0.7f);
	
	App->render->Blit(graphics, 0, 170, &ground);

	return UPDATE_CONTINUE;
}