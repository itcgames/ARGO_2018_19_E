#ifndef HEALTHCOMPONENT_H
#define HEALTHCOMPONENT_H

#include "Components.h"

class HealthComponent : public Component
{
public:
	HealthComponent(int health) : health(health) {}

	int getHealth() { return health; }
	void setHealth(int health) { this->health = health; }

	std::string m_tag = "HEALTH";

	std::string getType() { return m_tag; }

private:
	int health;
};
#endif // !HEALTHCOMPONENT_H
