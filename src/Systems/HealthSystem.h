#ifndef HEALTHSYSTEM_H
#define HEALTHSYSTEM_H

#include <iostream>
#include <vector>
#include "../Entity.h"

class HealthSystem
{
	std::vector<Entity *> m_entities;

public:
	HealthSystem();
	void addEntity(Entity * e);
	void update();
};
#endif // !HEALTHSYSTEM_H
