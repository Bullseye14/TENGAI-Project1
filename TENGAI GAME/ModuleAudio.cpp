#include "Globals.h"
#include "Application.h"
#include "ModuleAudio.h"

ModuleAudio::ModuleAudio(){ }

ModuleAudio::~ModuleAudio(){ }

bool ModuleAudio::Init() 
{
	LOG("Loading audio assets");
	bool ret = true;

	return ret;
}

update_status ModuleAudio::Update() 
{
	return UPDATE_CONTINUE;
}