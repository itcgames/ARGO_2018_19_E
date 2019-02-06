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

		// check gun player collide
		if (tc->getTag() == "Player")
		{
			playerPositionX = pc->getX();
			playerPositionY = pc->getY();
		}
		if (tc->getTag() == "Gun")
		{
			if (playerPositionX >= pc->getX() - 300 && playerPositionX <= pc->getX() + 300)
			{
		
				

				// Ensures angle reaches angleTo when the difference is very small
				//if (Math.abs(angleDifference) < 1) {
				//	angle = angleTo;
				//}

				//x = RCos(Angle)
				//y = RSin(Angle)
				double angleTo = cc->getAngle() + 90;
				//double angleDifference = (angleTo - angle + 180) % (360) - 180;
				double angleDifference = angleTo - angle;
				double ease = 0.15;
				angle += angleDifference * ease;

				double radAng = angle * 3.14159265359 / 180;
				double xOffset = 90 * (cos(radAng));
				double yOffset = 90 * (sin(radAng));

				pc->setX(playerPositionX + 50 - xOffset);
				pc->setY(playerPositionY + 40 + yOffset);
				
			}
		}

		if (tc->getTag() == "Gun")
		{
			sc->setRotation((cc->getAngle())*-1);
		}
		if (cc->getAngle() < 0)
		{
			sc->m_flipValue = SDL_FLIP_HORIZONTAL;
		}
		else {
			sc->m_flipValue = SDL_FLIP_NONE;
		}

		if (tc->getTag() == "Player")  // Replace with bool to check if gun is grabbed so gun falls
		{
			if (pc->getY() <= 500) {
				pc->setVelY(pc->getVelY() + Friction->y);
			}
			else {
				pc->setVelY(0);
			}
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
				cc->setJump(false);
			}
		}


		

		pc->setVelX(pc->getVelX() * Friction->x);

		pc->setX(pc->getX() + pc->getVelX());
		pc->setY(pc->getY() + pc->getVelY());
	}
}

