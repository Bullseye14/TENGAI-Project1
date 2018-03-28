#pragma once
#include "Module.h"
class ModuleAudio :
	public Module
{
public:
	ModuleAudio();
	~ModuleAudio();

	bool Init();
	update_status Update();

public:

};

