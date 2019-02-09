#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include <iostream>
#include <vector>
#include "../Entity.h"
#include "../MapLoader.h"
#include "ControlSystem.h"

class CollisionSystem
{
public:
	CollisionSystem();
	
	void addEntity(Entity * e);
	void update(std::vector<std::vector<Tile*>> tiles);
	std::string rectCollision(c2AABB A, c2AABB B);

	void checkBullets(PositionComponent * gun, std::vector<std::vector<Tile*>> tiles);


	std::vector<Entity *> m_entities;

	int m_count = 0;
	

};
#endif // !COLLISIONSYSTEM_H
