#include "PhysicsSystem.h"

PhysicsSystem::PhysicsSystem() {

}

void PhysicsSystem::addEntity(Entity * e) {
	m_entities.push_back(e);
}

void PhysicsSystem::update() {

	for (Entity * entity : m_entities) {

		ControlComponent * cc = (ControlComponent*)entity->getCompByType("CONTROL");
		PositionComponent * pc = (PositionComponent*)entity->getCompByType("POSITION");
		SpriteComponent * sc = (SpriteComponent*)entity->getCompByType("SPRITE");
		TagComponent * tc = (TagComponent*)entity->getCompByType("TAG");
		AIComponent * ac = (AIComponent*)entity->getCompByType("AI");

		// check gun player collide
		if (tc->getTag() == "Player")
		{
			playerPositionX = pc->getX();
			playerPositionY = pc->getY();
		}
		if (tc->getTag() == "Gun")
		{
			if (playerPositionX >= pc->getX() - 100 && playerPositionX <= pc->getX() + 100)
			{
				pc->setX(playerPositionX);
				pc->setY(playerPositionY);
			}

			if (aiPositionX >= pc->getX() - 100 && aiPositionX <= pc->getX() + 100)
			{
				pc->setX(aiPositionX);
				pc->setY(aiPositionY);
			}
		}

		if (tc->getTag() == "Gun")
		{
			sc->setRotation((cc->getAngle())*-1);

			if (cc->getAngle() < 0)
			{
				sc->m_flipValue = SDL_FLIP_HORIZONTAL;
			}
			else {
				sc->m_flipValue = SDL_FLIP_NONE;
			}
		}
		

		if (pc->getY() <= 500) {
			pc->setVelY(pc->getVelY() + Friction->y);
		}
		else {
			pc->setVelY(0);
		}
		
		if (tc->getTag() == "Player")
		{

			if (cc->getLeft()) {
				if (pc->getVelX() > -6.0) {
					pc->setVelX(pc->getVelX() - 1.5);
				}
			}
			if (cc->getRight()) {
				if (pc->getVelX() < 6.0) {
					pc->setVelX(pc->getVelX() + 1.5);
				}
			}
			if (cc->getJump() && pc->getY() >= 500) {
				pc->setVelY(pc->getVelY() - 20);
				pc->setY(500);
				cc->setJump(false);
			}

			if (cc->getAngle() < 0)
			{
				sc->m_flipValue = SDL_FLIP_HORIZONTAL;
			}
			else {
				sc->m_flipValue = SDL_FLIP_NONE;
			}
		}

		if (tc->getTag() == "AI_TAG")
		{
			aiPositionX = pc->getX();
			aiPositionY = pc->getY();

			if (ac->getJump() && pc->getY() >= 500) {
				pc->setVelY(pc->getVelY() - 20);
				pc->setY(500);
				ac->setJump(false);
			}


		}



		pc->setVelX(pc->getVelX() * Friction->x);

		pc->setX(pc->getX() + pc->getVelX());
		pc->setY(pc->getY() + pc->getVelY());
	}
}

