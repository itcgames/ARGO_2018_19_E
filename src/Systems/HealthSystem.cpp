#include "HealthSystem.h"

HealthSystem::HealthSystem() {

}

void HealthSystem::addEntity(Entity * e) {
	m_entities.push_back(e);
}

void HealthSystem::update() {

	for (Entity * entity : m_entities) {

		HealthComponent * hc = (HealthComponent*)entity->getCompByType("HEALTH");	
	}

}

