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

		if (pc->getY() <= 500) {
			pc->setVelY(pc->getVelY() + Friction->y);
		}
		else {
			pc->setVelY(0);
		}

		if (cc->getJump() && pc->getY() >= 500) {
			pc->setVelY(pc->getVelY() - 20);
			cc->setJump(false);
		}

		

		pc->setVelX(pc->getVelX() * Friction->x);

		pc->setX(pc->getX() + pc->getVelX());
		pc->setY(pc->getY() + pc->getVelY());
	}
}

