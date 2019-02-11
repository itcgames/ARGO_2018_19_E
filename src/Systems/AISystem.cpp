#include "AISystem.h"

AISystem::AISystem() {
	fsm = new Animation();
}

void AISystem::addEntity(Entity * e) {
	m_entities.push_back(e);
}

void AISystem::receive(std::vector<Entity*> ents)
{
	int count = 0;
	c2v vec = { 0.0f, 0.0f };
	m_distances.assign(ents.size(), std::make_pair(0.0, vec));
	
	for (auto e = ents.begin(); e != ents.end(); ++e)
	{
		PositionComponent  * pos = (PositionComponent*)(*e)->getCompByType("POSITION");
		ControlComponent * con = (ControlComponent*)(*e)->getCompByType("CONTROL");
		AIComponent * ac = (AIComponent*)(*e)->getCompByType("AI");
		
		
		m_distances[count].first = ac->distance(curPosition, pos->getX(), pos->getY());
			
		vec.x = pos->getX();
		vec.y = pos->getY();
			
		m_distances[count].second = vec;
		
		count++;
	}	
}

c2v AISystem::checkClosest(std::vector<std::pair<double, c2v>> distances)
{

	double smallest = 10000;

	for (auto it = distances.begin(); it != distances.end(); it++)
	{
		if (it->first != 0)
		{
			if (it->first < smallest) {
				smallest = it->first;
				m_realDist = (*it);
			}
		}
	}
	
	//need to fix to find closest;
	return m_realDist.second;
}

c2v AISystem::checkPoints(std::vector<c2v*> points, PositionComponent* pc)
{

	double smallest = 10000;

	c2v myPos = { pc->getX(), pc->getY() };
	c2v closestPosition;

	for (auto it = points.begin(); it != points.end(); it++)
	{
		//std::cout << (*it)->x << std::endl;
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

void AISystem::update(std::vector<c2v*> points) {
	
	
	int speed = 0;
	int x = 0;
	int y = 0;

	for (Entity * entity : m_entities) {

		PositionComponent * pc = (PositionComponent*)entity->getCompByType("POSITION");
		SpriteComponent * sc = (SpriteComponent*)entity->getCompByType("SPRITE");
		AIComponent * ac = (AIComponent*)entity->getCompByType("AI");
		FState *state = (FState*)entity->getCompByType("STATE");
		//CollisionComponent *coll = (CollisionComponent*)entity->getCompByType("COLLISION");

		if (ac->m_alive) {
			curPosition.x = pc->getX();
			curPosition.y = pc->getY();


			if (pc->getVelY() > 0.9 && pc->getVelY() < 1.0)
			{
				m_landed = true;
				
			}
			//closestEnemy = checkClosest(m_distances);
			if (m_landed) {
				closestPoint = checkPoints(points, pc);
			}
			if (curPosition.x > closestEnemy.x)
			{
				//sc->m_flipValue = SDL_FLIP_HORIZONTAL;
			}
			if (curPosition.x < closestEnemy.x)
			{
				//sc->m_flipValue = SDL_FLIP_NONE;

			}
			if (closestPoint.x > pc->getX())
			{
				facingRight = true;
				facingleft = false;
			}
			else
			{
				facingleft = true;
				facingRight = false;
			}

			
			if (facingleft && m_landed) {
				/*if (curPosition.x > closestPoint.x)
				{*/
				pc->setVelX(pc->getVelX() - 1.5);

				/*}*/
				if (curPosition.x < closestPoint.x  + 100/* && curPosition.x > closestPoint.x - 25*/ && m_landed)
				{
					pc->setVelX(pc->getVelX() - 4.0);
					ac->setJump(true);
					m_landed = false;

				}

			/*	if (pc->m_hitSide)
				{
					ac->setJump(true);
					pc->setVelX(pc->getVelX() - 8.0);
					pc->m_hitSide = false;
				}*/
			}

			if (facingRight && m_landed) {
				pc->setVelX(pc->getVelX() + 1.5);

				if (curPosition.x > closestPoint.x - 100/* && curPosition.x > closestPoint.x - 25*/ && m_landed)
				{
					pc->setVelX(pc->getVelX() + 4.0);
					ac->setJump(true);
					m_landed = false;

				}

				/*if (pc->m_hitSide)
				{
					ac->setJump(true);
					pc->setVelX(pc->getVelX() + 4.0);
					pc->m_hitSide = false;
				}*/
			}
			
			
			if (curPosition.x < closestPoint.x)
			{
				pc->setVelX(pc->getVelX() + 1.5);
			}

			//}

			////std::cout << "Ypos " << pc->getY() << std::endl;

			//if (curPosition.y > closestEnemy.y)
			//{
			//	ac->setJump(true);
			//}

			std::cout << "Point = " << closestPoint.x << ", " << closestPoint.y << std::endl;
			std::cout << "Position = " << curPosition.x << std::endl;
		}
		
		
	}

}


double AISystem::distance(c2v  vecOne, c2v vecTwo)
{
	return std::sqrt((vecOne.x - vecTwo.x) * (vecOne.x - vecTwo.x) + (vecOne.y - vecTwo.y) * (vecOne.y - vecTwo.y));
}


