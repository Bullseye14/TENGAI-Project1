#ifndef __Bullet_H__
#define __Bullet_H__


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

class Bullet {

public:
	Bullet();
	Bullet(Animation animation,int x, int y);
	~Bullet();

public:
	Animation animation;
	int x;
	int y;
};

#endif