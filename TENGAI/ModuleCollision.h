#ifndef __ModuleCollision_H__
#define __ModuleCollision_H__

#define MAX_COLLIDERS 500

#include "Module.h"

enum COLLIDER_TYPE
{
	COLLIDER_NONE = -1,
	COLLIDER_PLAYER,
	COLLIDER_ENEMY_BOSS,
	COLLIDER_SAMURAI,
	COLLIDER_ENEMY,
	COLLIDER_ENEMY_GREEN,
	COLLIDER_ENEMY_RED,
	COLLIDER_PLAYER_SHOT_P1,
	COLLIDER_PLAYER_SHOT_P2,
	COLLIDER_ENEMY_SHOT,
	COLLIDER_POWER_UP,

	COLLIDER_MAX
};

struct Collider
{
	SDL_Rect rect;
	bool to_delete = false;
	COLLIDER_TYPE type;
	Module* callback = nullptr;

	Collider(SDL_Rect rectangle, COLLIDER_TYPE type, Module* callback = nullptr) :
		rect(rectangle),
		type(type),
		callback(callback)
	{}

	void SetPos(int x, int y)
	{
 		rect.x = x;
		rect.y = y;
	}

	bool CheckCollision(const SDL_Rect& r) const;
};

class ModuleCollision : public Module
{
public:

	ModuleCollision();
	~ModuleCollision();

	update_status PreUpdate() override;
	bool Start();
	update_status Update() override;
	bool CleanUp() override;

	Collider* AddCollider(SDL_Rect rect, COLLIDER_TYPE type, Module* callback = nullptr);
	void DebugDraw();

private:

	Collider * colliders[MAX_COLLIDERS];
	bool matrix[COLLIDER_MAX][COLLIDER_MAX];
	bool debug = false;
	bool f5 = false;
};

#endif // __ModuleCollision_H__