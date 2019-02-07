#include "AISystem.h"

AISystem::AISystem() {

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
	for (auto it = distances.begin(); it != distances.end(); it++)
	{
		if (it->first != 0)
		{
			m_realDist = (*it);
		}
	}
	
	//need to fix to find closest;
	return m_realDist.second;
}

void AISystem::update() {
	
	
	int speed = 0;
	int x = 0;
	int y = 0;

	for (Entity * entity : m_entities) {

		PositionComponent * pc = (PositionComponent*)entity->getCompByType("POSITION");
		SpriteComponent * sc = (SpriteComponent*)entity->getCompByType("SPRITE");
		AIComponent * ac = (AIComponent*)entity->getCompByType("AI");

		if (ac->m_alive) {
			curPosition.x = pc->getX();
			curPosition.y = pc->getY();

			closestEnemy = checkClosest(m_distances);


			if (curPosition.x > closestEnemy.x)
			{
				sc->m_flipValue = SDL_FLIP_HORIZONTAL;
			}
			if (curPosition.x < closestEnemy.x)
			{
				sc->m_flipValue = SDL_FLIP_NONE;

			}

			if (curPosition.x > closestEnemy.x + 400)
			{
				pc->setVelX(pc->getVelX() - 1.5);
			}
			if (curPosition.x < closestEnemy.x - 400)
			{
				pc->setVelX(pc->getVelX() + 1.5);

			}

			//std::cout << "Ypos " << pc->getY() << std::endl;

			if (curPosition.y > closestEnemy.y)
			{
				ac->setJump(true);
			}
			//std::cout << ac->getJump() << std::endl;
			//std::cout << closestEnemy.x << ", " << closestEnemy.y << std::endl;
		}
		
		
	}

}

