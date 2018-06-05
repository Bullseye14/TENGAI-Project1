#ifndef __ModuleSceneSea_H__
#define __ModuleSceneSea_H__

#include "Module.h"

#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment(lib,"SDL_mixer/libx86/SDL2_mixer.lib")



class ModuleSceneSea : public Module
{
public:
	ModuleSceneSea();
	~ModuleSceneSea();

	bool Start();
	update_status Update();
	bool CleanUp();

	bool MoveCameraDown();

public:

	SDL_Texture * graphics = nullptr;
	SDL_Rect BG_Mountain;
	SDL_Rect layer_ocean_1;
	SDL_Rect layer_ocean_2;
	SDL_Rect layer_ocean_3;
	SDL_Rect layer_ocean_4;
	SDL_Rect layer_ocean_5;
	SDL_Rect static_layers;
	SDL_Rect Waterfall_bg;
	SDL_Rect scroll_bg;
	SDL_Rect sea_bg;
	SDL_Rect sea_scroll;
	SDL_Rect stone1;
	SDL_Rect stone2;
	SDL_Rect stone3;
	SDL_Rect transition;

	Animation waterfall1;
	Animation waterfall2;
	Animation waterfall3;
	Animation under_waterfall;
	Animation candle1;
	Animation candle2;
	Animation candle3;
	Animation wave;
	Animation big_waterfall;

	bool camera_moved;
	float speed = 5;
	int scroll_speed = 1;
	uint current_time, last_time_camera_down;

	int camera_trigger_down_x = 250;
	int camera_trigger_down_y = 300;
	int delta_camera = 0;


	Mix_Music* SceneSea = nullptr;

};

#endif // __ModuleSceneSea_H__
