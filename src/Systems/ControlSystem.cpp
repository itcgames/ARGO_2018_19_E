#include "ControlSystem.h"

ControlSystem::ControlSystem() {

}

void ControlSystem::addEntity(Entity * e) {
	m_entities.push_back(e);
}

void ControlSystem::update(SDL_Event & e) {

	for (Entity * entity : m_entities) {
		if (e.type == SDL_KEYDOWN) {
			int initX = 0;
			int initY = 0;
			int x = 0;
			int y = 0;


			switch (e.type)
			{
			case SDL_KEYDOWN:
				switch (e.key.keysym.sym)
				{
				case SDLK_UP:
					y--;
					break;
				case SDLK_DOWN:
					y++;
					break;
				case SDLK_RIGHT:
					x++;
					break;
				case SDLK_LEFT:
					x--;
					break;
				}
			}


			for (Entity * entity : m_entities) {
				PositionComponent * pc = (PositionComponent*)entity->getCompByType("POSITION");

			}
		}
	}
}

