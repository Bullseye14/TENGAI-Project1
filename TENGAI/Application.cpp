#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleSceneForest.h"
#include "ModuleMiko.h"
#include "ModuleFadeToBlack.h"
#include "ModuleParticles.h"
#include "ModuleSceneIntro.h"
#include "ModuleAudio.h"
#include "ModuleSceneOutro.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"
#include "ModuleJunis.h"
#include "ModuleSho.h"
#include "ModuleSceneRanking.h"
#include "ModuleFonts.h"
#include "ModuleSceneSea.h"

Application::Application()
{
	modules[0] = window = new ModuleWindow();
	modules[1] = render = new ModuleRender();
	modules[2] = input = new ModuleInput();
	modules[3] = textures = new ModuleTextures();
	modules[4] = audio = new ModuleAudio();
	modules[5] = scene_forest = new ModuleSceneForest();
	modules[6] = scene_sea = new ModuleSceneSea();
	modules[7] = enemies = new ModuleEnemies();
	modules[8] = miko = new ModuleMiko();
	modules[9] = junis = new ModuleJunis();
	modules[10] = sho = new ModuleSho();
	modules[11] = particles = new ModuleParticles();
	modules[12] = scene_outro = new ModuleSceneOutro();
	modules[13] = scene_ranking = new ModuleSceneRanking();
	modules[14] = scene_intro = new ModuleSceneIntro();
	modules[15] = collision = new ModuleCollision();
	modules[16] = fade = new ModuleFadeToBlack();
	modules[17] = fonts = new ModuleFonts();
	
	
}	

Application::~Application()
{
	for(int i = NUM_MODULES - 1; i >= 0; --i)
		delete modules[i];
}

bool Application::Init()
{
	bool ret = true;

	miko->Disable();
	junis->Disable();
	sho->Disable();
	enemies->Disable();
	scene_forest->Disable();
	scene_sea->Disable();
	scene_outro->Disable();
	scene_ranking->Disable();
	
	// ---

	for(int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->Init();

	for(int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Start() : true;

	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : UPDATE_CONTINUE;

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for(int i = NUM_MODULES - 1; i >= 0 && ret == true; --i)
		ret = modules[i]->CleanUp();

	return ret;
}