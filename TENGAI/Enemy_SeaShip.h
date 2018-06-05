#ifndef __ENEMY_SEASHIP_H__
#define __ENEMY_SEASHIP_H__

#include "Enemy.h"

class Enemy_SeaShip : public Enemy
{
private:

	int original_y = 0;
	int original_x = 0;
	iPoint original_position;
	Animation idle;
	Animation* current_animation = nullptr;
	Animation die;
	Path path;
	Path path2;

public:

	Enemy_SeaShip(int x, int y);
	Collider* enemy_collider;

	void Move();
};

#endif