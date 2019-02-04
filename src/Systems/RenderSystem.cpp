#include "RenderSystem.h"

RenderSystem::RenderSystem() {
	
}

void RenderSystem::addEntity(Entity * e) {
	m_entities.push_back(e);
}

void RenderSystem::update() {
	
	for (Entity * entity : m_entities) {
		
		//Render texture to screen
		PositionComponent * pc = (PositionComponent*)entity->getCompByType("POSITION");
		
		
	}


}


