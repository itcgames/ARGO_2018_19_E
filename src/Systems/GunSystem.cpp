#include "GunSystem.h"

GunSystem::GunSystem() {

}

void GunSystem::addEntity(Entity * e) {
	m_entities.push_back(e);
}

void GunSystem::update() {

	for (Entity * entity : m_entities) {

		//Render texture to screen
		PositionComponent * pc = (PositionComponent*)entity->getCompByType("POSITION");
		SpriteComponent * gc = (SpriteComponent*)entity->getCompByType("SPRITE");
		ControlComponent * cc = (ControlComponent*)entity->getCompByType("CONTROL");
		TagComponent * tc = (TagComponent*)entity->getCompByType("TAG");


		//std::cout << cc->getAngle() << std::endl;

		//if (tc->getTag() == "Gun")
		//{
			//gc->setRotation((cc->getAngle())*-1);
		//}

		//m_position = { pc->getX(), pc->getY(), 100,100 };
		//screenRect = { 0,0,1200,700 };
		//imageRect = { m_position };
		//centre.x = imageRect.w / 2;
		//centre.y = imageRect.h / 2;

		//SDL_QueryTexture(gc->getTexturePath(), nullptr, nullptr, gc->getW(), gc->getH());


		//SDL_RenderCopyEx(renderer, gc->getTexturePath(), &screenRect, &imageRect, 0, &centre, SDL_FLIP_NONE);
	}


}