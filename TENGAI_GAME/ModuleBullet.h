#ifndef __ModuleBullet_H__
#define __ModuleBullet_H__


#include "Animation.h"
#include "Globals.h"
#include "ModulePlayer.h"
#include "Module.h"



/*

enum bulletType
{
bullet,
secondBullet,
bomb,
specialAttack

};
*/

class ModuleBullet : public Module {
public:
	ModuleBullet();
	ModuleBullet(Animation animation, int x, int y);
	~ModuleBullet();

	bool Start();
	update_status Update();

	SDL_Texture* graphics = nullptr;
	Animation animation;
	int x;
	int y;
};

#endif