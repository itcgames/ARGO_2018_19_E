#ifndef GRENADESYSTEM_H
#define GRENADESYSTEM_H

#include <iostream>
#include <vector>
#include "../Entity.h"
#include "../AI.h"
#include "../Player.h"
#include "../cute_c2.h"
#include "../MapLoader.h"
#include "../ParticleExample.h"
#include "ControlSystem.h"

class GrenadeSystem
{
public:
	GrenadeSystem();
	void addEntity(Entity * e);
	void update(std::vector<std::shared_ptr<Tile>> tiles, std::vector<AI *> aiChars, std::vector<Player *> playerChars, Camera * camera);
	float dist(c2v v1, c2v v2);
	void render();
	void setRenderer(SDL_Renderer * renderer);
	void animateExplosion();
	ParticleExample * explode;
	float explodeX;
	float explodeY;

	int m_count = 0;
	bool m_startAnimating = false;

	std::vector<Entity *> m_entities;
};
#endif // !GRENADESYSTEM_H
