#ifndef __ModulePlayerMotor_H__
#define __ModulePlayerMotor_H__

#include "Module.h"
#include "Animation.h"
#include "ModulePlayer.h"
#include "Bullet.h"
#include "ModuleTextures.h"
#include <list>


class ModulePlayerMotor : public Module
{
public:
	ModulePlayerMotor();
	~ModulePlayerMotor();

	bool Start();
	update_status Update();
	void Shoot();


public:
	std::list<Bullet> magazineList;
	SDL_Texture* graphics = nullptr;
	ModulePlayer* thisPlayer = nullptr;

	Animation animation_bullet;;
	Animation secondBullet;
	Animation bomb;
	Animation specialAttack;

};

#endif