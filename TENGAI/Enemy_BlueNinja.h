#ifndef __ENEMY_BLUENINJA_H__
#define __ENEMY_BLUENINJA_H__

#include "Enemy.h"

class Enemy_BlueNinja : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	int original_y = 0;
	int original_x = 0;
	iPoint original_position;
	Animation fly;
	Animation floor;
	Animation run;
	Animation* current_animation = nullptr;
	Path path, path2;

public:

	Enemy_BlueNinja(int x, int y);
	Collider* enemy_collider;

	void Move();
	void Shoot();

	bool air = true;
	bool running = false;
};

#endif // __ENEMY_BROWNCOOKIE_H__
