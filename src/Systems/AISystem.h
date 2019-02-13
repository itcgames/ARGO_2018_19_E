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

	struct Line
	{
		float x1;
		float y1;
		float x2;
		float y2;
	};

public:
	AISystem();
	void addEntity(Entity * e);
	void update(std::vector<c2v*> points, std::vector<c2v*> walkpoints);
	c2v checkClosest(std::vector<std::pair<double, c2v>> distances, std::pair<double, c2v > real);
	double distance(c2v  vecOne, c2v vecTwo);
	c2v checkJumpPoints(std::vector<c2v*> points, PositionComponent* pc);
	c2v checkWalkPoints(std::vector<c2v*> points, PositionComponent* pc);
	void receive(std::vector<Entity*> ents);
	c2v getPosition(Entity * ent);

private:
	
	std::vector<std::pair<double, c2v>> m_dist;
	
	

	Animation *fsm;
	c2v m_position;
};



#endif // !AISYSTEM_H
