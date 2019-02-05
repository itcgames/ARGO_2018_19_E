#include "RenderSystem.h"

RenderSystem::RenderSystem() {
	
}

void RenderSystem::addEntity(Entity * e) {
	m_entities.push_back(e);
}

void RenderSystem::render(SDL_Renderer* renderer) {
	
	for (Entity * entity : m_entities) {
		

		SpriteComponent* sc = (SpriteComponent*)entity->getCompByType("SPRITE");
		
		sc->render(renderer);
	}


}


