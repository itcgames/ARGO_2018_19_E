#include "RenderSystem.h"

RenderSystem::RenderSystem() {
	
}

void RenderSystem::addEntity(Entity * e) {
	m_entities.push_back(e);
}

void RenderSystem::render(SDL_Renderer* renderer) {
	
	for (Entity * entity : m_entities) {

		PositionComponent* pc = (PositionComponent*)entity->getCompByType("POSITION");
		TagComponent* tc = (TagComponent*)entity->getCompByType("TAG");
		c2v newPos;
		newPos.x = pc->getX();
		newPos.y = pc->getY();
		SpriteComponent* sc = (SpriteComponent*)entity->getCompByType("SPRITE");
		sc->setPosition(newPos);
		sc->render(renderer);
	}


}


