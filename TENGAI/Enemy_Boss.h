#ifndef __ENEMY_BOSS_H__
#define __ENEMY_BOSS_H__

#include "Enemy.h"

class Enemy_Boss : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	int original_y = 0;
	int original_x = 0;
	iPoint original_position;
	Animation idle, open, shot, close, aftershot;
	Animation* current_animation = nullptr;
	Path path;
	Path path2;

public:

	Enemy_Boss(int x, int y);

	void Move();
	void Shoot();
};

#endif // __ENEMY_BOSS_H__
