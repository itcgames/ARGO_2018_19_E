#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <vector>
#include "./Components/AIComponent.h"
#include "./Components/ControlComponent.h"
#include "./Components/SpriteComponent.h"
#include "./Components/HealthComponents.h"
#include "./Components/PositionComponent.h"
#include "./Components/DisplayComponent.h"
#include "./Components/TagComponent.h"
#include "./Components/CollisionComponent.h"
#include "./Components/FactoryComponent.h"
#include "./Components/StateComponent.h"
#include "./Components/GrenadeComponent.h"
#include "./Components/RayCastComponent.h"
#include <SDL.h>

class Entity
{
public:
	Entity() {}
	virtual ~Entity() {};
	void addComponent(Component * newComp) {
		m_components.push_back(newComp);
	}

	void removeComponent(Component * removeComp) {

	}

	void addEntity(Entity * ent)
	{
		m_entities.push_back(ent);
	}

	std::vector<Entity*> getEntities(Entity * ent)
	{
		m_entities.push_back(ent);
	}

	void updatePosition()
	{

	}


	std::vector<Component*> getComponents() {
		return m_components;
	}

	Component * getCompByType(std::string tag) {
		for (Component * comp : m_components) {
			if (comp->getType() == tag) {
				return comp;
			}
		}
	}
private:
	std::vector<Component*> m_components;
	std::vector<Entity*> m_entities;
};


#endif // !ENTITY_H
