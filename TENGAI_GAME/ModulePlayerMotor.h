#ifndef __ModulePlayerMotor_H__
#define __ModulePlayerMotor_H__

#include "Module.h"
#include "Animation.h"
#include "ModuleTextures.h"


enum bulletType
{
	bullet,
	secondBullet,
	bomb,
	specialAttack

};

class ModulePlayerMotor : public Module
{
public:
	ModulePlayerMotor();
	~ModulePlayerMotor();

	bool Start();
	update_status Update();
	void Shoot();


public:
	SDL_Texture* graphics = nullptr;
	Animation bullet;
	Animation secondBullet;
	Animation bomb;
	Animation specialAttack;

};

#endif