#ifndef __ENEMY_BROWNCOOKIE_H__
#define __ENEMY_BROWNCOOKIE_H__

#include "Enemy.h"

class Enemy_BrownCookie : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	int original_y = 0;
	//iPoint position;
	Animation idle;

public:

	Enemy_BrownCookie(int x, int y);

	void Move();
	void Shoot();
};

#endif // __ENEMY_BROWNCOOKIE_H__
