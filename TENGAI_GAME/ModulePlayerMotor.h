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
	Bullet magazineList [50];
	SDL_Texture* graphics = nullptr;
	ModulePlayer* thisPlayer = nullptr;

	int bullets_shot, last_bullet_iterator,i_temp;
	unsigned int lastTime = 0, currentTime;
	Animation animation_bullet;;
	Animation secondBullet;
	Animation bomb;
	Animation specialAttack;

};

#endif