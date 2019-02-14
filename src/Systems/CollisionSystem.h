#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include <iostream>
#include <vector>
#include "../Entity.h"
#include "../MapLoader.h"
#include "ControlSystem.h"
#include "../ParticleExample.h"

class CollisionSystem
{
public:
	CollisionSystem();
	
	void addEntity(Entity * e);
	void update(std::vector<std::shared_ptr<Tile>> tiles);
	std::string rectCollision(c2AABB A, c2AABB B);

	void checkBullets(PositionComponent * gun, std::vector<std::shared_ptr<Tile>> tiles);
	void setRenderer(SDL_Renderer * renderer);
	void animateExplosion();
	void render();


	std::vector<Entity *> m_entities;

	int m_count = 0;
	c2v curPosition;
	bool m_startAnimating = false;
	std::vector<c2v*> positions;
	std::vector<ParticleExample*> m_particles;

	SDL_Renderer * m_renderer;
};
#endif // !COLLISIONSYSTEM_H
