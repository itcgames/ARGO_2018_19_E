#ifndef AISYSTEM_H
#define AISYSTEM_H

#include <iostream>
#include <vector>
#include "../Entity.h"
#include "../cute_math2d.h"


class AISystem
{
	std::vector<Entity *> m_entities;

	

public:
	AISystem();
	void addEntity(Entity * e);
	void update();
	void receive(Entity * e);
private:
	const v2 *Friction = new v2(0.90, 0.98);
	v2 playerPos;
};
#endif // !AISYSTEM_H
