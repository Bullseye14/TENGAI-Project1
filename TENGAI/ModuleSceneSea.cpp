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

}

ModuleSceneSea::~ModuleSceneSea()
{}

// Load assets5
bool ModuleSceneSea::Start()
{
	LOG("Loading sea scene");

	return true;
}

// UnLoad assets
bool ModuleSceneSea::CleanUp()
{
	LOG("Unloading sea scene");

	return true;
}

// Update: draw background
update_status ModuleSceneSea::Update()
{
	return UPDATE_CONTINUE;
}