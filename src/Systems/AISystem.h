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
	void update(std::vector<c2v*> points, std::vector<c2v*> walkpoints);
	c2v checkClosest(std::vector<std::pair<double, c2v>> distances);
	double distance(c2v  vecOne, c2v vecTwo);
	c2v checkJumpPoints(std::vector<c2v*> points, PositionComponent* pc);
	c2v checkWalkPoints(std::vector<c2v*> points, PositionComponent* pc);
	void receive(std::vector<Entity*> ents);

	std::vector<c2v*> checkTier(std::vector<c2v*> jumppoints);
private:
	c2v closestEnemy;
	c2v closestJumpPoint;
	c2v closestWalkPoint;
	std::vector<std::pair<double, c2v>> m_distances;
	std::pair<double, c2v> m_realDist;

	c2v curPosition;
	bool m_landed;
	Animation *fsm;

	bool facingleft = false;
	bool facingRight = false;


	bool tierOne = true;
	bool tierTwo = false;
	bool tierThree = false;
};
#endif // !AISYSTEM_H
