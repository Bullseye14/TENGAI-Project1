#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

/* CONTROLS:
	UP, DOWN, LEFT, RIGHT => MOVEMENT
	S = SHIELD/TURN 
	D = DIE/REVIVE
	R = RUN
*/
struct SDL_Texture;

class ModulePlayer : public Module
{
public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status Update();

public:

	SDL_Texture* miko_texture = nullptr;
	SDL_Rect miko;

	Animation* current_animation;
	Animation idle;
	Animation backward;
	Animation run;
	Animation die;
	Animation shield;
	Animation bullet;
	iPoint position;

	bool alive;
	int speed;
	uint last_time, current_time;

};

#endif