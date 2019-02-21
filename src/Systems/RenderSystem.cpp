#include "RenderSystem.h"

RenderSystem::RenderSystem() {
	
}

void RenderSystem::addEntity(Entity * e) {
	m_entities.push_back(e);
}

void RenderSystem::render(SDL_Renderer* renderer, Camera* camera) {
	
	for (Entity * entity : m_entities) {

		PositionComponent* pc = (PositionComponent*)entity->getCompByType("POSITION");
		TagComponent* tc = (TagComponent*)entity->getCompByType("TAG");
		c2v offset;
		offset = c2v{ static_cast<float>(pc->getX() - camera->getCamera()->x), static_cast<float>(pc->getY() - camera->getCamera()->y) };
	
		SpriteComponent* sc = (SpriteComponent*)entity->getCompByType("SPRITE");
		sc->setPosition(offset);
		sc->render(renderer);
	}


}


