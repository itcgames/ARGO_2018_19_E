#ifndef PHYSICSSYSTEM_H
#define PHYSICSSYSTEM_H

#include <iostream>
#include <vector>
#include "../Entity.h"
#include "../cute_c2.h"

class PhysicsSystem
{
public:
	std::vector<Entity *> m_entities;

	
	c2v Friction;

	PhysicsSystem();
	void addEntity(Entity * e);
	void update();
	void receive(Entity * e);
	double playerPositionX = 0;
	double playerPositionY = 0;
};
#endif // !PHYSICSSYSTEM_H
