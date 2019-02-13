#ifndef GRENADESYSTEM_H
#define GRENADESYSTEM_H

#include <iostream>
#include <vector>
#include "../Entity.h"
#include "../AI.h"
#include "../cute_c2.h"
#include "../MapLoader.h"
#include "../ParticleExample.h"

class GrenadeSystem
{
	std::vector<Entity *> m_entities;

public:
	GrenadeSystem();
	void addEntity(Entity * e);
	void update(std::vector<std::vector<Tile*>> tiles, std::vector<AI *> aiChars);
	float dist(c2v v1, c2v v2);
	void render();
	void setRenderer(SDL_Renderer * renderer);
	void animateExplosion();
	ParticleExample * explode;
	float explodeX;
	float explodeY;

	int m_count = 0;
	bool m_startAnimating = false;
};
#endif // !GRENADESYSTEM_H
