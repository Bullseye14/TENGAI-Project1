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
	Animation idle;
	Animation* current_animation = nullptr;
	Animation die;
	Path path;

public:

	Enemy_Boss(int x, int y);

	//void Die();
	void Move();
	void Shoot();
	//void OnCollision(Collider* c1, Collider* c2);

	int Elife = 20;
	bool alive = true;
};

#endif // __ENEMY_BOSS_H__