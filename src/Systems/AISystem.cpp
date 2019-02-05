#include "AISystem.h"

AISystem::AISystem() {

}

void AISystem::addEntity(Entity * e) {
	m_entities.push_back(e);
}

void AISystem::receive(Entity * e)
{
	PositionComponent  * j = (PositionComponent*)e->getCompByType("POSITION");
	playerPos.x = (float)j->getX();
	playerPos.y = (float)j->getX();
}

void AISystem::update() {
	
	int speed = 0;
	int x = 0;
	int y = 0;

	for (Entity * entity : m_entities) {

		PositionComponent * pc = (PositionComponent*)entity->getCompByType("POSITION");
		SpriteComponent * sc = (SpriteComponent*)entity->getCompByType("SPRITE");
		AIComponent * ac = (AIComponent*)entity->getCompByType("AI");
		
		pc->setVelX(pc->getVelX() + 1.5);
	
		if (ac->getJump() && pc->getY() >= 500) {
			pc->setVelY(pc->getVelY() - 20);
			ac->setJump(false);
		}

		std::cout << playerPos.x << ", " << playerPos.y << std::endl;
		
		pc->setVelX(pc->getVelX() * Friction->x);

		pc->setX(pc->getX() + pc->getVelX());
		pc->setY(pc->getY() + pc->getVelY());
	}

}

