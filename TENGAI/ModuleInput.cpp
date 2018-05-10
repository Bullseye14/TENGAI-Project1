#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"


ModuleInput::ModuleInput() : Module()
{
	for(uint i = 0; i < MAX_KEYS; ++i)
		keyboard[i] = KEY_IDLE;
}

// Destructor
ModuleInput::~ModuleInput()
{
}

// Called before render is available
bool ModuleInput::Init()
{
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if (SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER) < 0) 
	{
		LOG("SDL_GAMECONTROLLER could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	if (SDL_NumJoysticks() < 2) 
	{
		LOG("Warning! There is no joystick connected!");
	}
	else 
	{
		gamepad = SDL_GameControllerOpen(0);
		gamepad2 = SDL_GameControllerOpen(1);
		if (gamepad == NULL) 
		{
			LOG("Warning! Unable to open GameController. SDL_Error: %s\n", SDL_GetError());
		}
		if (gamepad2 == NULL)
		{
			LOG("Warning! Unable to open GameController. SDL_Error: %s\n", SDL_GetError());
		}
	}

	return ret;
}

// Called every draw update
update_status ModuleInput::PreUpdate()
{
	SDL_PumpEvents();

	const Uint8* keys = SDL_GetKeyboardState(NULL);

	for(int i = 0; i < MAX_KEYS; ++i)
	{
		if(keys[i] == 1)
		{
			if(keyboard[i] == KEY_IDLE)
				keyboard[i] = KEY_DOWN;
			else
				keyboard[i] = KEY_REPEAT;
		}
		else
		{
			if(keyboard[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
				keyboard[i] = KEY_UP;
			else
				keyboard[i] = KEY_IDLE;
		}
	}
	while (SDL_PollEvent(&Event)) {
		if (Event.type == SDL_QUIT)
			return update_status::UPDATE_STOP;
	}
	if(keyboard[SDL_SCANCODE_ESCAPE])
		return update_status::UPDATE_STOP;

	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	SDL_GameControllerClose(gamepad);
	gamepad = NULL;
	SDL_GameControllerClose(gamepad2);
	gamepad2 = NULL;
	SDL_QuitSubSystem(SDL_INIT_GAMECONTROLLER);
	return true;
}