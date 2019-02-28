#include "RestartSystem.h"

RestartSystem::RestartSystem() {

}

void RestartSystem::addEntity(Entity * e) {
	m_entities.push_back(e);
}


void RestartSystem::reset(int level, std::vector<std::pair<bool, c2v>*>  vec, bool online, int clientNum, int size) {
	
	int count = 0;

	for (Entity * ent : m_entities) {

		TagComponent * tc = (TagComponent*)ent->getCompByType("TAG");
		PositionComponent * pc = (PositionComponent*)ent->getCompByType("POSITION");
		SpriteComponent * sc = (SpriteComponent*)ent->getCompByType("SPRITE");
		AIComponent * ac = (AIComponent*)ent->getCompByType("AI");

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
			tc->setGunGotID("0");
			tc->setBalloonDeflate(false);
			control->setThrowGun(false);
			control->setAlive(true);
			control->setAngle(90);
			control->isDead = false;
		}

		if (!online) {

			if (tc->getSubTag2() == "AI_Player")
			{
				ac->initRecieve = false;
				ac->set = false;
				pc->setX(vec.at(count)->second.x);
				pc->setY(vec.at(count)->second.y);
				sc->setPosition(c2v{ vec.at(count)->second.x, vec.at(count)->second.y });
				count++;
			}
			else if (tc->getTag() == "Player")	
			{
				pc->setX(vec.at(count)->second.x);
				pc->setY(vec.at(count)->second.y);
				sc->setPosition(c2v{ vec.at(count)->second.x, vec.at(count)->second.y });
				count++;
			}
		}
		else
		{
			if (vec.at(clientNum - 1)->first == false)
			{
				pc->setX(vec.at(clientNum - 1)->second.x);
				pc->setY(vec.at(clientNum - 1)->second.y);
				sc->setPosition(c2v{ vec.at(clientNum - 1)->second.x, vec.at(clientNum - 1)->second.y });
				vec.at(clientNum - 1)->first = true;
			}
			if (clientNum < size) {
				for (int i = clientNum + 1; i <= size; i++) {
					if (vec.at(i - 1)->first == false)
					{
						pc->setX(vec.at(i - 1)->second.x);
						pc->setY(vec.at(i - 1)->second.y);
						sc->setPosition(c2v{ vec.at(i - 1)->second.x, vec.at(clientNum - 1)->second.y });
						vec.at(i - 1)->first = true;
					}
				}
			}

			if (clientNum > 1) {
				for (int i = clientNum - 1; i > 0; i--) {
					if (vec.at(i - 1)->first == false)
					{
						pc->setX(vec.at(i - 1)->second.x);
						pc->setY(vec.at(i - 1)->second.y);
						sc->setPosition(c2v{ vec.at(i - 1)->second.x, vec.at(clientNum - 1)->second.y });
						vec.at(i - 1)->first = true;
					}
				}
			}
		}
		
		if (tc->getTag() == "Hand") {
			tc->setGunGot("none");
			tc->setGunGotID("0");
			tc->setGotGunBool(false);
		}
		if (tc->getTag() == "Gun") {
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