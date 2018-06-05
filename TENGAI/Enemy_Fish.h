#ifndef __ENEMY_FISH_H__
#define __ENEMY_FISH_H__

#include "Enemy.h"

class Enemy_Fish : public Enemy 
{
private:

	int original_y = 0;
	int original_x = 0;
	iPoint original_position;
	Animation idle;
	Animation attack;
	Animation* current_animation = nullptr;
	Animation die;
	Path path;

	Path attack1;
	Path attack2;

	Path move;
	Path path2;

public:
	Enemy_Fish(int x, int y);
	Collider* enemy_collider;

	void Move();
	void Shoot();
};

#endif