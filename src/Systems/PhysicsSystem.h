#ifndef PHYSICSSYSTEM_H
#define PHYSICSSYSTEM_H

#include <iostream>
#include <vector>
#include "../Entity.h"
#include "../cute_math2d.h"

class PhysicsSystem
{
public:
	std::vector<Entity *> m_entities;

	
	const v2 *Friction = new v2(0.90, 0.98);

	PhysicsSystem();
	void addEntity(Entity * e);
	void update();
	double playerPositionX = 0;
	double playerPositionY = 0;

	double angle = 0;
};
#endif // !PHYSICSSYSTEM_H
