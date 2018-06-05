#ifndef __ENEMY_METALIC_GREEN_H__
#define __ENEMY_METALIC_GREEN_H__

#include "Enemy.h"

class Enemy_MetalicGreen : public Enemy
{
private:

	int original_y = 0;
	int original_x = 0;
	iPoint original_position;
	Animation idle;
	Animation* current_animation = nullptr;
	Animation die;
	Path pathup;
	Path pathdown;
	Path path2;
	int screen = 1;

public:

	Enemy_MetalicGreen(int x, int y);
	Collider* enemy_collider;

	void Move();
};

#endif