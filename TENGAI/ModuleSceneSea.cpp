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
#include "ModuleCollision.h"
#include "ModuleEnemies.h"
#include "Enemy_Boss.h"
#include "ModuleJunis.h"
#include "ModuleSceneRanking.h"
#include "ModuleSceneSea.h"

ModuleSceneSea::ModuleSceneSea()
{
	// waves
	waves1.x = 801;
	waves1.y = 88;
	waves1.w = 960;
	waves1.h = 16;

	waves2.x = 801;
	waves2.y = 115;
	waves2.w = 960;
	waves2.h = 16;

	waves3.x = 800;
	waves3.y = 145;
	waves3.w = 960;
	waves3.h = 20;

	waves4.x = 801;
	waves4.y = 176;
	waves4.w = 960;
	waves4.h = 20;

	waves5.x = 801;
	waves5.y = 206;
	waves5.w = 960;
	waves5.h = 41;

	// background far
	BG_far.x = 0;
	BG_far.y = 0;
	BG_far.w = 756;
	BG_far.h = 128;


}

ModuleSceneSea::~ModuleSceneSea()
{
}

// Load assets5
bool ModuleSceneSea::Start()
{
	LOG("Loading sea scene");

	graphics1 = App->textures->Load("assets/tengai/Water/SeaBG.png");

	App->collision->Enable();
	App->enemies->Enable();
	App->miko->Enable();
	App->junis->Enable();

	/*App->miko->score = 0;
	App->junis->score = 0;*/

	SceneSea = App->audio->LoadMusic("assets/audio/audiosea.ogg");
	Mix_PlayMusic(SceneSea, -1);

	return true;
}

// UnLoad assets
bool ModuleSceneSea::CleanUp()
{
	LOG("Unloading sea scene");

	App->textures->Unload(graphics1);
	App->miko->Disable();
	App->junis->Disable();
	App->collision->Disable();
	App->enemies->Disable();

	return true;
}

// Update: draw background
update_status ModuleSceneSea::Update()
{
	// Move camera forward -----------------------------
	int scroll_speed = 1;
	float speed = 5;

	//Player auto scroll
	App->miko->position.x += speed / SCREEN_SIZE / 2;
	App->junis->position.x += speed / SCREEN_SIZE / 2;

	App->render->camera.x -= speed / SCREEN_SIZE / 2;

	int pos = -9, postree = -10, pos2 = 809, pos4 = 780;

	// Draw everything --------------------------------------
	//App->render->Blit(background, 0, 0, NULL);
	/*for (int i = 0; i < 6; ++i) {
		App->render->Blit(graphics, pos, 0, &BG_far, 0.55f);
		App->render->Blit(graphics, pos + 170, 26, &tree2, 0.60f);
		App->render->Blit(graphics, pos + 42, 45, &tree3, 0.60f);
		App->render->Blit(graphics, pos, 58, &BG_mid, 0.60f);
		App->render->Blit(graphics, postree, 83, &tree1, 0.65f);

		pos += 319;
		postree += 318;
	}
	for (int i = 0; i < 15; i++) {
		App->render->Blit(graphics, pos4, 193, &ground, 0.75f);
		pos4 += ground.w;
	}

	App->render->Blit(graphics, 0, 0, &floor1, 0.75f);
	App->render->Blit(graphics, 115, 0, &TempleDoor, 0.75f);
	App->render->Blit(graphics, 938, 140, &ForestHouse1, 0.75f);
	App->render->Blit(graphics, 1400, 92, &ForestHouse2, 0.75f);

	for (int i = 0; i < 5; i++) {
		App->render->Blit(graphics, pos2, 204, &floor2, 0.75f);
		pos2 += floor2.w;
	}
	App->render->Blit(graphics, 1600, 185, &floor3, 0.75f);
	App->render->Blit(graphics, 1764, 0, &floor4, 0.75f);
	App->render->Blit(graphics, 2019, 0, &floor5, 0.75f);*/

	if (App->miko->MikoLife == 3 && App->junis->JunisLife == 3)
	{
		App->fade->FadeToBlack(App->scene_sea, App->scene_outro, 2.0);
		App->miko->MikoLife = 1;
		App->junis->JunisLife = 1;
	}
	if (App->input->keyboard[SDL_SCANCODE_F2] == KEY_STATE::KEY_REPEAT)
	{
		App->miko->won = true;
		App->junis->won = true;
	}

	if (App->miko->won == true || App->junis->won == true)
	{
		App->miko->Win();
		App->junis->Win();
		App->fade->FadeToBlack(App->scene_sea, App->scene_ranking, 3.0);
	}

	return UPDATE_CONTINUE;
}