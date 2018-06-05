#ifndef __ENEMY_SAMURAI_H__
#define __ENEMY_SAMURAI_H__

#include "Enemy.h"

class Enemy_Samurai : public Enemy
{
private:

	int original_y = 0;
	int original_x = 0;
	iPoint original_position;
	Animation idle;
	Animation wave;
	Animation* current_animation = nullptr;
	Animation die;
	Path path;
	Path path2;

public:

	Enemy_Samurai(int x, int y);
	Collider* enemy_collider;

	void Move();
};

#endif