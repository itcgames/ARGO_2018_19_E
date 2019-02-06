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
	void receive(std::vector<Entity*> ents);
private:
	const c2v *Friction = new c2v{ 0.90f, 0.98f };
	c2v closestEnemy;

	std::vector<double> m_distances;
};
#endif // !AISYSTEM_H
