#ifndef SOUNDSYSTEM_H
#define SOUNDSYSTEM_H

#include <iostream>
#include <vector>
#include "../Entity.h"
#include <SDL_image.h>
#include <string>

using namespace std;

class SoundSystem
{
	std::vector<Entity *> m_entities;

public:
	SoundSystem();
	void addEntity(Entity * e);
	void render(SDL_Renderer* renderer);

private:

};
#endif // !SOUNDSYSTEM_H
