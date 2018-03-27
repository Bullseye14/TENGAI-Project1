#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleUI.h"



ModuleUI::ModuleUI()
{
	p1.x = 27;
	p1.y = 1390;
	p1.w = 65;
	p1.h = 50;
}


ModuleUI::~ModuleUI()
{
}

bool ModuleUI::Start()
{
	UI_texture = App->textures->Load("UISpritesheet.png");
	return true;
}

update_status ModuleUI::Update()
{
	
	App->render->Blit(UI_texture, 0, 0, &p1, 0.0f);

	return UPDATE_CONTINUE;
}
