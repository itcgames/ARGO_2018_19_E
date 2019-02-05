#include "RenderSystem.h"

RenderSystem::RenderSystem() {
	
}

void RenderSystem::addEntity(Entity * e) {
	m_entities.push_back(e);
}

void RenderSystem::render(SDL_Renderer* renderer) {
	
	for (Entity * entity : m_entities) {

		PositionComponent* pc = (PositionComponent*)entity->getCompByType("POSITION");
		v2 newPos = v2(pc->getX(), pc->getY());
		SpriteComponent* sc = (SpriteComponent*)entity->getCompByType("SPRITE");
		sc->setPosition(newPos);
		
		sc->render(renderer);
	}


}


