#include "RenderSystem.h"

RenderSystem::RenderSystem() {
	
}

void RenderSystem::addEntity(Entity * e) {
	m_entities.push_back(e);
}

void RenderSystem::render(SDL_Renderer* renderer) {
	
	for (Entity * entity : m_entities) {
		
		SDL_Rect m_position;
		SDL_Rect imageRect;
		SDL_Point centre;

		//Render texture to screen
		PositionComponent * pc = (PositionComponent*)entity->getCompByType("POSITION");
		SpriteComponent * gc = (SpriteComponent*)entity->getCompByType("SPRITE");
		DisplayComponent * dc = (DisplayComponent*)entity->getCompByType("DISPLAY");

		m_position = { pc->getX(), pc->getY(),  *gc->getW(), *gc->getH()};
		imageRect = { m_position };
		centre.x = imageRect.w / 2;
		centre.y = imageRect.h / 2;

		SDL_QueryTexture(gc->getTexturePath(), nullptr, nullptr, gc->getW(), gc->getH());	
		SDL_RenderCopyEx(renderer, gc->getTexturePath(), dc->getScreenRect(), &imageRect, 0, &centre, SDL_FLIP_NONE);
	}


}


