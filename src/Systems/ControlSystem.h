#ifndef CONTROLSYSTEM_H
#define CONTROLSYSTEM_H

#include <iostream>
#include <vector>
#include "../Entity.h"

class ControlSystem
{
public:
	ControlSystem();
	void init();
	void addEntity(Entity * e);
	void update(SDL_Event e);

	std::vector<Entity *> m_entities;
	SDL_GameController* gGameController = NULL;
	const int JOYSTICK_DEAD_ZONE = 8000;

	int aIndex = 0;

	double joystickAngle = 0;
};
#endif // !CONTROLSYSTEM_H
