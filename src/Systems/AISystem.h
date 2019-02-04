#ifndef AISYSTEM_H
#define AISYSTEM_H

#include <iostream>
#include <vector>
#include "../Entity.h"

class AISystem
{
	std::vector<Entity *> m_entities;

public:
	AISystem();
	void addEntity(Entity * e);
	void update();
};
#endif // !AISYSTEM_H
