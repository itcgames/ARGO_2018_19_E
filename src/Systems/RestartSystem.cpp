#include "RestartSystem.h"

RestartSystem::RestartSystem() {

}

void RestartSystem::addEntity(Entity * e) {
	m_entities.push_back(e);
}

void RestartSystem::reset(int level) {
	
	for (Entity * ent : m_entities) {

		TagComponent * tc = (TagComponent*)ent->getCompByType("TAG");
		PositionComponent * pc = (PositionComponent*)ent->getCompByType("POSITION");
		SpriteComponent * sc = (SpriteComponent*)ent->getCompByType("SPRITE");

		pc->setVelX(0);
		pc->setVelY(0);
		pc->setX(pc->startX);
		pc->setY(pc->startY);
		sc->setRotation(0);
		sc->setPosition(c2v{pc->startX, pc->startY});

	
		if (tc->getTag() == "Player") {
			ControlComponent * control = (ControlComponent*)ent->getCompByType("CONTROL");
			tc->setGunGot("none");
			tc->setGotGunBool(false);
			control->setThrowGun(false);
			control->setAlive(true);
			control->setAngle(90);
		}
		else if (tc->getTag() == "Hand") {
			tc->setGunGot("none");
			tc->setGotGunBool(false);
		}
		else if (tc->getTag() == "Gun") {
			CollisionComponent * colisionc = (CollisionComponent*)ent->getCompByType("COLLISION");
			colisionc->setW(sc->getWidth());
			colisionc->setH(sc->getHeight());
			tc->setGrabable(true);
			tc->setGrabbed(false);
			tc->setGrabableCount(0);
			if (tc->getSubTag() == "grenade") {
				GrenadeComponent * grenade = (GrenadeComponent*)ent->getCompByType("GRENADE");
				grenade->setArmed(false);
				grenade->setExplode(false);
				grenade->setTTL(200);
			}
		}
	}

	
}