#include "AISystem.h"

AISystem::AISystem() {

}

void AISystem::addEntity(Entity * e) {
	m_entities.push_back(e);
}

void AISystem::receive(std::vector<Entity*> ents)
{
	
	
	for (auto e = ents.begin(); e != ents.end(); ++e)
	{
		m_distances.assign(ents.size(), 0.0);
		PositionComponent  * pos = (PositionComponent*)(*e)->getCompByType("POSITION");
		ControlComponent * con = (ControlComponent*)(*e)->getCompByType("CONTROL");
		//if (pos->getX() != )
	}

	
	
}

void AISystem::update() {
	
	int speed = 0;
	int x = 0;
	int y = 0;

	for (Entity * entity : m_entities) {

		PositionComponent * pc = (PositionComponent*)entity->getCompByType("POSITION");
		SpriteComponent * sc = (SpriteComponent*)entity->getCompByType("SPRITE");
		AIComponent * ac = (AIComponent*)entity->getCompByType("AI");
		
	
		

		
	}

}

