#include "GrenadeSystem.h"

GrenadeSystem::GrenadeSystem() {

}

void GrenadeSystem::addEntity(Entity * e) {
	m_entities.push_back(e);
}

void GrenadeSystem::update(std::vector<std::vector<Tile*>>  tiles) {

	for (Entity * entity : m_entities) {

		PositionComponent * pc = (PositionComponent*)entity->getCompByType("POSITION");
		GrenadeComponent * gc = (GrenadeComponent*)entity->getCompByType("GRENADE");
		if (gc->getExplode()) {
			float explodeX = pc->getX();
			float explodeY = pc->getY();
			
			for (int i = 0; i < tiles.size(); i++) {
				for (int j = 0; j < tiles[i].size(); j++) {
					c2v v1 = { tiles[i].at(j)->dRect.x + 35, tiles[i].at(j)->dRect.y + 35 };
					c2v v2 = { explodeX, explodeY };
					if (dist(v1, v2) < 200.0) {
						tiles[i].at(j)->dead = true;
					}
				}
			}
			// James please add big boom here :)
			pc->setX(-3000);
			pc->setY(-3000);
			gc->setArmed(false);
		}
	}

}

float GrenadeSystem::dist(c2v v1, c2v v2) {
	float dist = std::sqrt(((v1.x - v2.x) * (v1.x - v2.x)) + ((v1.y - v2.y) * (v1.y - v2.y)));
	return dist;
}

