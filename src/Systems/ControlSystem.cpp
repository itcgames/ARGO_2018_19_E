#include "ControlSystem.h"

ControlSystem::ControlSystem() {
	init();
}

void ControlSystem::init() {
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}

	//Set texture filtering to linear
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		printf("Warning: Linear texture filtering not enabled!");
	}

	//Check for joysticks
	if (SDL_NumJoysticks() < 1)
	{
		printf("Warning: No joysticks connected!\n");
	}
	else
	{
		//Load joystick
		gGameController = SDL_GameControllerOpen(0);
		if (gGameController == NULL)
		{
			printf("Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError());
		}
	}
}

void ControlSystem::addEntity(Entity * e) {
	m_entities.push_back(e);
}

void ControlSystem::update(SDL_Event e) {

	

	for (Entity * entity : m_entities) {


		ControlComponent * cc = (ControlComponent*)entity->getCompByType("CONTROL");
		int StickX = SDL_GameControllerGetAxis(gGameController, SDL_CONTROLLER_AXIS_LEFTX);
		int StickY = SDL_GameControllerGetAxis(gGameController, SDL_CONTROLLER_AXIS_LEFTY);

		int leftX = SDL_GameControllerGetAxis(gGameController, SDL_CONTROLLER_AXIS_RIGHTX);
		int leftY = SDL_GameControllerGetAxis(gGameController, SDL_CONTROLLER_AXIS_RIGHTY);

		setButtons(*cc);

		if (StickX < -JOYSTICK_DEAD_ZONE) {
			cc->setLeft(true);
		}
		else {
			cc->setLeft(false);
		}

		if (StickX > JOYSTICK_DEAD_ZONE) {

		cc->setRight(true);
		}
		else {
			cc->setRight(false);
		}
		
		if (leftX > JOYSTICK_DEAD_ZONE || leftX < -JOYSTICK_DEAD_ZONE ||
			leftY > JOYSTICK_DEAD_ZONE || leftY < -JOYSTICK_DEAD_ZONE) {
			joystickAngle = atan2((double)leftX, (double)leftY) * (180.0 / M_PI);
		}
		else {
			joystickAngle = 0.0;
		}
		cc->setAngle(joystickAngle);

		//std::cout << joystickAngle << std::endl;
	}
}

void ControlSystem::setButtons(ControlComponent & cc) {

	bool AButton = SDL_GameControllerGetButton(gGameController, SDL_CONTROLLER_BUTTON_A);
	bool XButton = SDL_GameControllerGetButton(gGameController, SDL_CONTROLLER_BUTTON_X);
	
	//int leftX = SDL_GameControllerGetAxis(gGameController, SDL_CONTROLLER_AXIS_RIGHTX);
	int RT = SDL_GameControllerGetAxis(gGameController, SDL_CONTROLLER_AXIS_TRIGGERRIGHT);
	
	if (RT > 5000) {
		cc.setFire(true);
	}
	else {
		cc.setFire(false);
	}

	if (AButton) {
		if (aIndex == 0)
			cc.setJump(AButton);
		aIndex++;
	}
	else {
		aIndex = 0;
	}
	if (XButton) {
		if (xIndex == 0)
			cc.setThrowWeapon(true);
		xIndex++;
	}
	else {
		xIndex = 0;
	}
}

