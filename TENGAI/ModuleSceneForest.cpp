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
#include "ModuleSho.h"
#include "ModuleSceneRanking.h"
#include "ModuleSceneSea.h"

ModuleSceneForest::ModuleSceneForest()
{
	// ground
	ground.x = 510;
	ground.y = 210;
	ground.w = 63;
	ground.h = 31;

	// Background Mid
	BG_mid.x = 1221;
	BG_mid.y = 2;
	BG_mid.w = 319;
	BG_mid.h = 135;

	// background far
	BG_far.x = 1495;
	BG_far.y = 140;
	BG_far.w = 319;
	BG_far.h = 223;

	// temple's door
	TempleDoor.x = 2;
	TempleDoor.y = 3;
	TempleDoor.w = 149;
	TempleDoor.h = 223;

	// forest houses
	ForestHouse1.x = 22;
	ForestHouse1.y = 238;
	ForestHouse1.w = 347;
	ForestHouse1.h = 54;

	ForestHouse2.x = 150;
	ForestHouse2.y = 109;
	ForestHouse2.w = 161;
	ForestHouse2.h = 109;

	// trees
	tree1.x = 154;
	tree1.y = 2;
	tree1.w = 318;
	tree1.h = 63;

	tree2.x = 154;
	tree2.y = 68;
	tree2.w = 114;
	tree2.h = 32;

	tree3.x = 478;
	tree3.y = 52;
	tree3.w = 14;
	tree3.h = 13;

	tree4.x = 1149;
	tree4.y = 267;
	tree4.w = 319;
	tree4.h = 96;

	tree5.x = 2196;
	tree5.y = 493;
	tree5.w = 316;
	tree5.h = 274;

	trees.x = 826;
	trees.y = 140;
	trees.w = 319;
	trees.h = 223;

	//logs 
	log1.x = 284;
	log1.y = 85;
	log1.w = 124;
	log1.h = 207;

	log2.x = 1874;
	log2.y = 24;
	log2.w = 616;
	log2.h = 207;

	//floors
	floor1.x = 15;
	floor1.y = 367;
	floor1.w = 809;
	floor1.h = 223;

	floor2.x = 828;
	floor2.y = 571;
	floor2.w = 159;
	floor2.h = 19;

	floor3.x = 990;
	floor3.y = 552;
	floor3.w = 164;
	floor3.h = 38;

	floor4.x = 1158;
	floor4.y = 367;
	floor4.w = 255;
	floor4.h = 223;

	floor5.x = 1417;
	floor5.y = 367;
	floor5.w = 671;
	floor5.h = 223;

	floor6.x = 2092;
	floor6.y = 552;
	floor6.w = 96;
	floor6.h = 38;

	//sky
	sky.x = 1874;
	sky.y = 240;
	sky.w = 707;
	sky.h = 120;

	//mountain
	mountain.x = 1216;
	mountain.y = 2;
	mountain.w = 511;
	mountain.h = 130;

}

ModuleSceneForest::~ModuleSceneForest()
{}

// Load assets5
bool ModuleSceneForest::Start()
{
	LOG("Loading forest scene");

	graphics = App->textures->Load("assets/tengai/BG_Sprites.png");
	
	App->render->camera.x = 0;
	App->render->camera.y = 0;

	App->collision->Enable();
	App->enemies->Enable();

	App->miko->Enable();
	App->sho->Enable();

	App->miko->path_win.Reset();
	App->sho->path_win.Reset();

	App->miko->won = false;
	App->sho->won = false;

	App->miko->MikoLife = 3;
	App->sho->ShoLife = 3;

	SceneForest = App->audio->LoadMusic("assets/audio/audioforest.ogg");
	Mix_PlayMusic(SceneForest, -1);

	App->enemies->AddEnemy(ENEMY_TYPES::BOSS, 800, 50);
	App->enemies->AddEnemy(ENEMY_TYPES::BOSS, 1600, 50);

	App->enemies->AddEnemy(ENEMY_TYPES::GREEN_SHIP, 520, 20);
	App->enemies->AddEnemy(ENEMY_TYPES::GREEN_SHIP, 550, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::GREEN_SHIP, 580, 100);
	App->enemies->AddEnemy(ENEMY_TYPES::RED_SHIP, 610, 140);

	App->enemies->AddEnemy(ENEMY_TYPES::GREEN_SHIP, 1020, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::GREEN_SHIP, 1050, 100);
	App->enemies->AddEnemy(ENEMY_TYPES::GREEN_SHIP, 1080, 140);
	App->enemies->AddEnemy(ENEMY_TYPES::RED_SHIP, 1110, 180);

	App->enemies->AddEnemy(ENEMY_TYPES::GREEN_SHIP, 1520, 40);
	App->enemies->AddEnemy(ENEMY_TYPES::GREEN_SHIP, 1550, 80);
	App->enemies->AddEnemy(ENEMY_TYPES::GREEN_SHIP, 1580, 120);
	App->enemies->AddEnemy(ENEMY_TYPES::RED_SHIP, 1610, 160);
	
	for (int j = 1; j < 9; j++) 
	{
		int space2 = 250;
		App->enemies->AddEnemy(ENEMY_TYPES::BLUE_NINJA, 200 + space2*j, 0);
		App->enemies->AddEnemy(ENEMY_TYPES::BLUE_NINJA, 230 + space2*j, 0);
		App->enemies->AddEnemy(ENEMY_TYPES::BLUE_NINJA, 270 + space2*j, 0);
		App->enemies->AddEnemy(ENEMY_TYPES::BLUE_NINJA, 300 + space2*j, 0);
	}  
	return true;
}

// UnLoad assets
bool ModuleSceneForest::CleanUp()
{
	LOG("Unloading forest scene");

	App->textures->Unload(graphics);
	App->audio->UnloadMusic(SceneForest);
	App->miko->Disable();
	App->sho->Disable();

	App->collision->Disable();
	App->enemies->Disable();

	return true;
}

// Update: draw background
update_status ModuleSceneForest::Update()
{
	// Move camera forward -----------------------------
	int scroll_speed = 1;
	float speed = 5;

	//Player auto scroll
	App->miko->position.x += speed / SCREEN_SIZE / 2;
	App->sho->position.x += speed / SCREEN_SIZE / 2;

	App->render->camera.x -= speed / SCREEN_SIZE / 2;

	int pos = -9, postree = -10, pos2 = 809, pos4 = 780;

	// Draw everything --------------------------------------
	for (int i = 0; i < 6; ++i) {
		App->render->Blit(graphics, pos, 0, &BG_far, 0.55f);
		App->render->Blit(graphics, pos+170, 26, &tree2, 0.60f);
		App->render->Blit(graphics, pos+42, 45, &tree3, 0.60f);
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
	App->render->Blit(graphics, 2019, 0, &floor5, 0.75f);


	if (App->miko->MikoLife <= 0 && App->sho->ShoLife <= 0)
	{
		App->fade->FadeToBlack(App->scene_forest, App->scene_outro, 2.0);
	}
	if (App->input->keyboard[SDL_SCANCODE_F2] == KEY_STATE::KEY_REPEAT) 
	{
		App->miko->won = true;
		App->sho->won = true;
	}
	if (App->input->keyboard[SDL_SCANCODE_F3] == KEY_STATE::KEY_REPEAT)
	{
		App->fade->FadeToBlack(App->scene_forest, App->scene_outro, 3.0f);
	}
	if (App->miko->position.x >= 2500) { App->miko->won = true; }

	if (App->sho->position.x >= 2500) { App->sho->won = true; }

	if (App->miko->won == true || App->sho->won == true) 
	{
		App->miko->Win();
		App->sho->Win();
		App->fade->FadeToBlack(App->scene_forest, App->scene_ranking, 0.5f);
	}

	return UPDATE_CONTINUE;
}