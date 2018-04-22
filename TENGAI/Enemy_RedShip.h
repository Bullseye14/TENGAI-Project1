#ifndef __ENEMY_REDSHIP_H__
#define __ENEMY_REDSHIP_H__

#include "Enemy.h"

class Enemy_RedShip : public Enemy
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

	Enemy_RedShip(int x, int y);
	Collider* enemy_collider;

	void Move();
};

#endif // __ENEMY_BROWNCOOKIE_H__
