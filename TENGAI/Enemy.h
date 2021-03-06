#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "p2Point.h"
#include "Animation.h"
#include "Path.h"
#include "SDL\include\SDL_timer.h"


struct SDL_Texture;
struct Collider;

class Enemy
{
protected:
	Collider* collider = nullptr;
	uint current_time;
	uint last_time;

public:
	
	iPoint position;

public:
	Enemy(int x, int y);
	virtual ~Enemy();

	const Collider* GetCollider() const;

	virtual void Move() {};
	virtual void Draw(SDL_Texture* sprites);
	virtual void PowerUp();
	int EnemyLife;
	bool alive = true;
	Animation* animation = nullptr;
};

#endif // __ENEMY_H__