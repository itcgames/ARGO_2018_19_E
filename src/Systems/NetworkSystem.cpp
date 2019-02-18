#include "NetworkSystem.h"

NetworkSystem::NetworkSystem() {

}

void NetworkSystem::addEntity(Entity * e) {
	m_entities.push_back(e);
}

void NetworkSystem::update(Packet * p) {
	for (Entity * ent : m_entities) {
		ControlComponent * cc = (ControlComponent*)ent->getCompByType("CONTROL");
		if (p->playerNum == cc->m_playerNum) {
			cc->setLeft(p->left);
			cc->setRight(p->right);
			cc->setAngle(p->gunAngle);
			cc->setAlive(p->alive);
			cc->setThrowWeapon(p->throwWeapon);
			cc->setJump(p->jump);
			cc->setFire(p->fire);
		}
	}
}