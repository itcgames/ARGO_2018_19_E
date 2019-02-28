#ifndef CONTROLSYSTEM_H
#define CONTROLSYSTEM_H

#include <iostream>
#include <vector>
#include "../Entity.h"

class ControlSystem
{
public:
	ControlSystem();
	SDL_Haptic* init(SDL_GameController* controller);
	void addEntity(Entity * e);
	void removeEntity(int index);
	void update(SDL_Event e);

	SDL_Haptic * haptic;
	void recieveLevel(int width, int height);

	void setButtons(ControlComponent* cc);

	std::vector<Entity *> m_entities;
	
	const int JOYSTICK_DEAD_ZONE = 8000;
	
	int aIndex = 0;
	int xIndex = 0;

	
	int m_width;
	int m_height;
};
#endif // !CONTROLSYSTEM_H
