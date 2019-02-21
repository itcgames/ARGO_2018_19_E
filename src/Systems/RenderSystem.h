#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include <iostream>
#include <vector>
#include "../Entity.h"
#include <SDL_image.h>
#include <string>

using namespace std;

class RenderSystem
{
public:
	RenderSystem();
	void addEntity(Entity * e);
	void render(SDL_Renderer* renderer);

	std::vector<Entity *> m_entities;
private:

};
#endif // !RENDERSYSTEM_H
