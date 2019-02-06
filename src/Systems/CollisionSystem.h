#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include <iostream>
#include <vector>
#include "../Entity.h"

class CollisionSystem
{
public:
	CollisionSystem();
	
	void addEntity(Entity * e);
	void update();
	int rectCollision(c2AABB A, c2AABB B);


	std::vector<Entity *> m_entities;

};
#endif // !COLLISIONSYSTEM_H
