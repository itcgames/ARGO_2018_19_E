#ifndef AISYSTEM_H
#define AISYSTEM_H

#include <iostream>
#include <vector>
#include "../Entity.h"
#include "../cute_c2.h"
#include <algorithm>
#include "../Animation.h"


class AISystem
{
	std::vector<Entity *> m_entities;

	

public:
	AISystem();
	void addEntity(Entity * e);
	void update(std::vector<c2v*> points);
	c2v checkClosest(std::vector<std::pair<double, c2v>> distances);
	c2v checkPoints(std::vector<c2v*> points);
	void receive(std::vector<Entity*> ents);
private:
	c2v closestEnemy;

	std::vector<std::pair<double, c2v>> m_distances;
	std::pair<double, c2v> m_realDist;

	c2v curPosition;

	Animation *fsm;
};
#endif // !AISYSTEM_H
