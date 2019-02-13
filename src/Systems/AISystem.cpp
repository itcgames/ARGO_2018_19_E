#include "AISystem.h"

AISystem::AISystem() {
	fsm = new Animation();
}

void AISystem::addEntity(Entity * e) {
	m_entities.push_back(e);
}

void AISystem::receive(std::vector<Entity*> ents)
{
	
	c2v vec = { 0.0f, 0.0f };
	for (Entity * entity : m_entities) {
		AIComponent * ac = (AIComponent*)entity->getCompByType("AI");
		int count = 0;
		ac->m_distances.assign(ents.size(), std::make_pair(0.0, vec));
		m_dist = ac->m_distances;
		for (auto e = ents.begin(); e != ents.end(); ++e)
		{
			PositionComponent  * pos = (PositionComponent*)(*e)->getCompByType("POSITION");
			ControlComponent * con = (ControlComponent*)(*e)->getCompByType("CONTROL");

			m_position = c2v{ pos->getX(), pos->getY() };
			//PositionComponent  * pos = (PositionComponent*)(*e)->getCompByType("POSITION");

		//std::cout << ac->curPosition.x << ", " << ac->curPosition.y << std::endl;
			ac->m_distances[count].first = distance(ac->curPosition, m_position);

			vec.x = pos->getX();
			vec.y = pos->getY();

			ac->m_distances[count].second = vec;


			count++;
		}
	}
}

c2v AISystem::checkClosest(std::vector<std::pair<double, c2v>> distances, std::pair<double, c2v > real)
{

	double smallest = 10000;

	for (auto it = distances.begin(); it != distances.end(); it++)
	{
		if (it->first != 0)
		{
			if (it->first < smallest) {
				smallest = it->first;
				real = (*it);
			}
		}
	}
	
	return real.second;
}

c2v AISystem::checkJumpPoints(std::vector<c2v*> points, PositionComponent* pc)
{

	double smallest = 10000;

	c2v myPos = { pc->getX(), pc->getY() };
	c2v closestPosition;

	for (auto it = points.begin(); it != points.end(); it++)
	{
		auto pos = c2v{ (*it)->x, (*it)->y };
		double dist = distance(myPos, pos);

		if (dist < smallest)
		{
			smallest = dist;
			closestPosition = pos;
		}
	}
	return closestPosition;
}

c2v AISystem::checkWalkPoints(std::vector<c2v*> points, PositionComponent* pc)
{

	double smallest = 10000;

	c2v myPos = { pc->getX(), pc->getY() };
	c2v closestPosition;

	for (auto it = points.begin(); it != points.end(); it++)
	{
		auto pos = c2v{ (*it)->x, (*it)->y };
		double dist = distance(myPos, pos);

		if (dist < smallest)
		{
			smallest = dist;
			closestPosition = pos;
		}
	}
	return closestPosition;
}

void AISystem::update(std::vector<c2v*> jumppoints, std::vector<c2v*> walkpoints) {
	
	
	int speed = 0;
	int x = 0;
	int y = 0;

	for (Entity * entity : m_entities) {

		PositionComponent * pc = (PositionComponent*)entity->getCompByType("POSITION");
		SpriteComponent * sc = (SpriteComponent*)entity->getCompByType("SPRITE");
		AIComponent * ac = (AIComponent*)entity->getCompByType("AI");
		FState *state = (FState*)entity->getCompByType("STATE");
		//CollisionComponent *coll = (CollisionComponent*)entity->getCompByType("COLLISION");

		ac->curPosition.x = pc->getX();
		ac->curPosition.y = pc->getY();

		if (ac->m_alive) {
			

			
			ac->newYVel = pc->getVelY();
			if (ac->newYVel != ac->oldYVel)
			{
				ac->m_landed = false;
				ac->oldYVel = ac->newYVel;
			}
			else
			{
				ac->m_landed = true;
			}
			


			if (ac->curPosition.x > ac->closestWalkPoint.x)
			{
				ac->facingleft = true;
				ac->facingRight = false;
				sc->m_flipValue = SDL_FLIP_HORIZONTAL;
			}
			else
			{
				ac->facingRight = true;
				ac->facingleft = false;

				sc->m_flipValue = SDL_FLIP_NONE;
			}


			ac->closestEnemy = checkClosest(ac->m_distances, ac->m_realDist);

			
			if (ac->m_landed) {
				//closestJumpPoint = checkJumpPoints(jumppoints, pc);

				ac->closestWalkPoint = checkWalkPoints(walkpoints, pc);

			}
		

			if (!ac->m_gunInSight) {
				if (ac->facingleft && ac->m_landed)
				{
					ac->setLeft(true);
					ac->setRight(false);

					if (ac->curPosition.x < ac->closestWalkPoint.x + 10)
					{
						if (pc->getVelX() < -7.8)
						{
							ac->setJump(true);
						}
						else
						{
							pc->setVelX(-8);
							ac->setJump(true);
						}

					}
				}
				if (ac->facingRight && ac->m_landed)
				{
					ac->setRight(true);
					ac->setLeft(false);

					if (ac->curPosition.x > ac->closestWalkPoint.x - 10)
					{
						if (pc->getVelX() > 7.8)
						{
							ac->setJump(true);
						}
						else
						{
							pc->setVelX(8);
							ac->setJump(true);
						}
					}
				}
			}
			//std::cout << ac->closestEnemy.x << ", " << ac->closestEnemy.y << std::endl;
			if (ac->curPosition.y > ac->closestEnemy.y && ac->curPosition.y < ac->closestEnemy.y + 200 && ac->m_landed)
			{
				ac->m_gunInSight = true;

				if (ac->closestEnemy.x < ac->curPosition.x)
				{
					ac->setRight(false);
					ac->setLeft(true);
				}
				if (ac->closestEnemy.x > ac->curPosition.x)
				{
					ac->setRight(true);
					ac->setLeft(false);
				}

				
			}
			
		}
		else
		{

		}
		
		
	}

}


double AISystem::distance(c2v  vecOne, c2v vecTwo)
{
	return std::sqrt((vecOne.x - vecTwo.x) * (vecOne.x - vecTwo.x) + (vecOne.y - vecTwo.y) * (vecOne.y - vecTwo.y));
}






